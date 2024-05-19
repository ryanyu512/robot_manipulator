// Include the ROS library
 #include <ros/ros.h>

// Include opencv2
#include <opencv2/core/mat.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


// Include CvBridge, Image Transport, Image msg
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <sensor_msgs/PointCloud2.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Pose.h>

// Include tf2 for transformation
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

#include "extract_pose_service/object_and_target_position.h"

// Topics
static const std::string IMAGE_TOPIC = "/camera1/rgb/image_raw";
static const std::string POINT_CLOUD2_TOPIC = "/camera1/depth/points";

// Publisher
ros::Publisher pub;

tf2_ros::Buffer tf_buffer;

const std::string from_frame = "camera_depth_optical_frame";
const std::string to_frame = "base_link";

cv::Mat camera_image;

cv::Point2f object_centroid;
cv::Point2f target_centroid;
bool is_no_obj = false;
double yaw_ang;

geometry_msgs::Point object_position_base_frame;
geometry_msgs::Point target_position_base_frame;

void search_centroid_in_area(std::vector<cv::Point2f> centroid_vector, 
                             cv::Rect area, 
                             std::vector<cv::Point2f> &centroid, 
                             std::vector<int> &target_ind) {


  for( int i = 0; i<centroid_vector.size(); i++) {
    if(centroid_vector[i].inside(area)) {
      centroid.push_back(centroid_vector[i]);
      target_ind.push_back(i);
    }
  }

  return;
}

void detect_edge(const cv::Mat &camera_image,
                 cv::Mat &canny_output) {

  // convert the image to grayscale format
  cv::Mat img_gray;
  cv::cvtColor(camera_image, img_gray, cv::COLOR_BGR2GRAY);
  cv::Canny(img_gray,canny_output,10,350);

  return;
}

void detect_contours(const cv::Mat &canny_output, 
                     std::vector<std::vector<cv::Point>> &contours,
                     std::vector<cv::Vec4i> &hierarchy){

    cv::findContours(canny_output, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);
}

void merge_centroids_and_contours(const std::vector<cv::Point2f> &centroids, 
                                const std::vector<std::vector<cv::Point>> &contours, 
                                std::vector<cv::Point2f> &merge_centroids,
                                std::vector<std::vector<cv::Point>> &merge_contours){

    std::vector<bool> is_visit(centroids.size(), false);
    std::vector<int> neighbor(centroids.size(), -1);
    double min_d_threshold = 2.;
    int new_contour_size = 0;

    for (int i = 0; i < centroids.size(); i ++){
        if (is_visit[i])
            continue;

        is_visit[i] = true;

        int min_ind  = -1;
        double min_d = std::numeric_limits<double>::infinity();

        for (int j = i + 1; j < centroids.size(); j ++){
            if (is_visit[j])
                continue;

            double dx = centroids[i].x - centroids[j].x;
            double dy = centroids[i].y - centroids[j].y;
            double d = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));

            if (d < min_d){
                min_d = d;
                min_ind = j;
            }
        }

        if (min_d < min_d_threshold){
            if (is_visit[min_ind] == false){
                is_visit[min_ind] = true;
                neighbor[i] = min_ind;
            }
        } 
        new_contour_size += 1;
    }

    merge_contours.resize(new_contour_size);
    merge_centroids.resize(new_contour_size);
    std::vector<bool> is_visit2(centroids.size(), false);
    for (int i = 0, k = 0; i < neighbor.size(); i ++){
        if (is_visit2[i] == true)
            continue;

        is_visit2[i] = true;
        merge_contours[k] = contours[i];
        merge_centroids[k] = centroids[i];

        if (neighbor[i] != -1){
            int nid = neighbor[i];
            for (int j = 0; j < contours[nid].size(); j ++)
                merge_contours[k].push_back(contours[nid][j]);

            merge_centroids[k] += centroids[nid];
            is_visit2[nid] = true;
        }
        merge_centroids[k].x /= 2.f;
        merge_centroids[k].y /= 2.f;

        k += 1;
    }

}

void drawAxis(cv::Mat& img, 
              cv::Point p, 
              cv::Point q, 
              cv::Scalar colour, 
              const float scale = 0.2){

    double angle = atan2( (double) p.y - q.y, (double) p.x - q.x ); // angle in radians
    double hypotenuse = sqrt( (double) (p.y - q.y) * (p.y - q.y) + (p.x - q.x) * (p.x - q.x));
    
    // Here we lengthen the arrow by a factor of scale
    q.x = (int) (p.x - scale * hypotenuse * cos(angle));
    q.y = (int) (p.y - scale * hypotenuse * sin(angle));
    cv::line(img, p, q, colour, 1, cv::LINE_AA);
    
    // create the arrow hooks
    p.x = (int) (q.x + 9 * cos(angle + CV_PI / 4));
    p.y = (int) (q.y + 9 * sin(angle + CV_PI / 4));
    cv::line(img, p, q, colour, 1, cv::LINE_AA);
    
    p.x = (int) (q.x + 9 * cos(angle - CV_PI / 4));
    p.y = (int) (q.y + 9 * sin(angle - CV_PI / 4));
    cv::line(img, p, q, colour, 1, cv::LINE_AA);
}

double getOrientation(const std::vector<cv::Point> &pts, 
                      cv::Mat &img){

    //Construct a buffer used by the pca analysis
    int sz = static_cast<int>(pts.size());
    cv::Mat data_pts = cv::Mat(sz, 2, CV_64F);
    for (int i = 0; i < data_pts.rows; i++){
        data_pts.at<double>(i, 0) = pts[i].x;
        data_pts.at<double>(i, 1) = pts[i].y;
    }
    
    //Perform PCA analysis
    cv::PCA pca_analysis(data_pts, cv::Mat(), cv::PCA::DATA_AS_ROW);
    
    //Store the center of the object
    cv::Point cntr = cv::Point(static_cast<int>(pca_analysis.mean.at<double>(0, 0)),
    static_cast<int>(pca_analysis.mean.at<double>(0, 1)));
    
    //Store the eigenvalues and eigenvectors
    std::vector<cv::Point2d> eigen_vecs(2);
    std::vector<double> eigen_val(2);
    for (int i = 0; i < 2; i++)
    {
        eigen_vecs[i] = cv::Point2d(pca_analysis.eigenvectors.at<double>(i, 0),
        pca_analysis.eigenvectors.at<double>(i, 1));
        eigen_val[i] = pca_analysis.eigenvalues.at<double>(i);
    }
    
    // Draw the principal components
    cv::circle(img, cntr, 3, cv::Scalar(255, 0, 255), 2);
    cv::Point p1 = cntr + 0.02 * cv::Point(static_cast<int>(eigen_vecs[0].x * eigen_val[0]), static_cast<int>(eigen_vecs[0].y * eigen_val[0]));
    cv::Point p2 = cntr - 0.02 * cv::Point(static_cast<int>(eigen_vecs[1].x * eigen_val[1]), static_cast<int>(eigen_vecs[1].y * eigen_val[1]));
    drawAxis(img, cntr, p1, cv::Scalar(  0, 255, 0), 5);
    drawAxis(img, cntr, p2, cv::Scalar(255, 255, 0), 5);
    
    double angle = std::atan2(eigen_vecs[0].y, eigen_vecs[0].x); // orientation in radians

    return angle;
}

void extract_centroids(std::vector<std::vector<cv::Point>> contours, 
                       std::vector<cv::Point2f> &centroids) {

    // get the moments
    std::vector<cv::Moments> mu(contours.size());
    for( int i = 0; i<contours.size(); i++ ){ 
        mu[i] = cv::moments( contours[i], false ); 
    }

    // get the centroid of figures.
    centroids.resize(contours.size());

    for( int i = 0; i<contours.size(); i++) {
        float centroid_x = mu[i].m10/mu[i].m00;
        float centroid_y = mu[i].m01/mu[i].m00;
        centroids[i] = cv::Point2f(centroid_x, centroid_y);
    }

    return;
}

void image_sub_callback(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try{
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
    catch (cv_bridge::Exception& e){
        ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
    }


    float image_size_y = cv_ptr->image.rows;
    float image_size_x = cv_ptr->image.cols;

    //detect edge
    cv::Mat canny_output;
    detect_edge(cv_ptr->image, canny_output);
    
   
    // detect the contours on the binary image using cv2.CHAIN_APPROX_NONE
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    detect_contours(canny_output, contours, hierarchy);
    
    // extract centroids of all contours
    std::vector<cv::Point2f> centroids;
    extract_centroids(contours, centroids);

    // merge contour 
    std::vector<cv::Point2f> merge_centroids;
    std::vector<std::vector<cv::Point>> merge_contours;
    merge_centroids_and_contours(centroids, contours, merge_centroids, merge_contours);

    // for visualisation
    cv::Mat drawing(canny_output.size(), CV_8UC3, cv::Scalar(255,255,255));

    //get box locations in 2d image
    cv::Rect box_search_area((image_size_x/2), 0, (image_size_x/2), (image_size_y/2));
    std::vector<cv::Point2f> c_object_centroid;
    std::vector<int> c_box_ind;
    search_centroid_in_area(merge_centroids, 
                            box_search_area,
                            c_object_centroid,
                            c_box_ind);

    if (c_object_centroid.size()){
        object_centroid = c_object_centroid[0];
        yaw_ang = getOrientation(merge_contours[c_box_ind[0]], drawing);
        is_no_obj = false;
        std::cout << "c_object_centroid.size(): " << c_object_centroid.size() << std::endl;
    }
    else
        is_no_obj = true;

    // draw contours
    for( int i = 0; i < merge_contours.size(); i++ ){
        if (merge_centroids[i].inside(box_search_area)){
            cv::Scalar color = cv::Scalar(167,151,0); // B G R values
            cv::drawContours(drawing, merge_contours, i, color, 2, 8, hierarchy, 0, cv::Point());
            cv::circle( drawing, merge_centroids[i], 4, color, -1, 8, 0 );
        }
    }

    // show the resuling image
    cv::namedWindow( "Extracted centroids", cv::WINDOW_AUTOSIZE );
    cv::imshow( "Extracted centroids", drawing );
    cv::waitKey(3);
}


geometry_msgs::Point pixel_to_3d_point(const sensor_msgs::PointCloud2 pCloud, const int u, const int v){

  // get width and height of 2D point cloud data
  int width = pCloud.width;
  int height = pCloud.height;

  // Convert from u (column / width), v (row/height) to position in array
  // where X,Y,Z data starts
  int arrayPosition = v*pCloud.row_step + u*pCloud.point_step;

  // compute position in array where x,y,z data start
  int arrayPosX = arrayPosition + pCloud.fields[0].offset; // X has an offset of 0
  int arrayPosY = arrayPosition + pCloud.fields[1].offset; // Y has an offset of 4
  int arrayPosZ = arrayPosition + pCloud.fields[2].offset; // Z has an offset of 8

  float X = 0.0;
  float Y = 0.0;
  float Z = 0.0;

  memcpy(&X, &pCloud.data[arrayPosX], sizeof(float));
  memcpy(&Y, &pCloud.data[arrayPosY], sizeof(float));
  memcpy(&Z, &pCloud.data[arrayPosZ], sizeof(float));

  geometry_msgs::Point p;
  p.x = X;
  p.y = Y;
  p.z = Z;

  return p;
}

geometry_msgs::Point transform_between_frames(geometry_msgs::Point p, const std::string from_frame, const std::string to_frame) {
    
  geometry_msgs::PoseStamped input_pose_stamped;
  input_pose_stamped.pose.position = p;
  input_pose_stamped.header.frame_id = from_frame;
  input_pose_stamped.header.stamp = ros::Time::now();

  geometry_msgs::PoseStamped output_pose_stamped = tf_buffer.transform(input_pose_stamped, to_frame, ros::Duration(1));
  return output_pose_stamped.pose.position;
}

void point_cloud_callback(const sensor_msgs::PointCloud2 pCloud) {
  
  //convert to 3d point 
  geometry_msgs::Point box_position_camera_frame;
  box_position_camera_frame = pixel_to_3d_point(pCloud, object_centroid.x, object_centroid.y);
  //transform to base frame    
  //to_frame = base_link, from_frame = depth camera
  object_position_base_frame = transform_between_frames(box_position_camera_frame, from_frame, to_frame);
  
  //target position is hard-coded here (it is usually not crticial)
  target_position_base_frame.x = -0.30;
  target_position_base_frame.y =  0.50;
  target_position_base_frame.z =  0.05;

  ROS_INFO_STREAM("3d object position relative to base frame: x " << object_position_base_frame.x << " y " << object_position_base_frame.y << " z " << object_position_base_frame.z);
  ROS_INFO_STREAM("3d target position relative to base frame: x " << target_position_base_frame.x << " y " << target_position_base_frame.y << " z " << target_position_base_frame.z);
}

// service call response
bool get_object_and_target_position(extract_pose_service::object_and_target_position::Request  &req,
                                    extract_pose_service::object_and_target_position::Response &res) {
      res.object_position = object_position_base_frame;
      res.target_position = target_position_base_frame;
      res.is_no_obj       = is_no_obj;
      res.yaw_ang         = yaw_ang;

      return true;
}

 // Main function
int main(int argc, char **argv)
{
// The name of the node
ros::init(argc, argv, "extract_pose_service");

// Default handler for nodes in ROS
ros::NodeHandle nh("");

// Used to publish and subscribe to images
image_transport::ImageTransport it(nh);

// Subscribe to the /camera raw image topic
image_transport::Subscriber image_sub = it.subscribe(IMAGE_TOPIC, 1, image_sub_callback);

// Subscribe to the /camera PointCloud2 topic
ros::Subscriber point_cloud_sub = nh.subscribe(POINT_CLOUD2_TOPIC, 1, point_cloud_callback);

tf2_ros::TransformListener listener(tf_buffer);

ros::ServiceServer service = nh.advertiseService("object_and_target_position",  get_object_and_target_position);

// Make sure we keep reading new video frames by calling the imageCallback function
ros::spin();

// Close down OpenCV
cv::destroyWindow("view");
}

 

