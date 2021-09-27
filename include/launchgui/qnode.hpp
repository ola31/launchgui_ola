/**
 * @file /include/launchgui/qnode.hpp
 *
 * @brief Communications central!
 *
 * @date February 2011
 **/
/*****************************************************************************
** Ifdefs
*****************************************************************************/

#ifndef launchgui_QNODE_HPP_
#define launchgui_QNODE_HPP_

/*****************************************************************************
** Includes
*****************************************************************************/

// To workaround boost/qt4 problems that won't be bugfixed. Refer to
//    https://bugreports.qt.io/browse/QTBUG-22829
#ifndef Q_MOC_RUN
#include <ros/ros.h>

#include <string>
#include <QThread>
#include <QStringListModel>
#include <std_msgs/UInt16.h>
//#include <sensor_msgs/Image.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
//#include <image_transport/image_transport.h>
#endif


/*****************************************************************************
** Namespaces
*****************************************************************************/

namespace launchgui {

/*****************************************************************************
** Class
*****************************************************************************/

class QNode : public QThread {
    Q_OBJECT
public:
	QNode(int argc, char** argv );
	virtual ~QNode();
	bool init();
	bool init(const std::string &master_url, const std::string &host_url);
	void run();

        void A_state_Callback(const std_msgs::UInt16& state_msg);
        void D_state_Callback(const std_msgs::UInt16& state_msg);
        void O_state_Callback(const std_msgs::UInt16& state_msg);
        void P_state_Callback(const std_msgs::UInt16& state_msg);
        void S_state_Callback(const std_msgs::UInt16& state_msg);
        void MD_state_Callback(const std_msgs::UInt16& state_msg);
        void JOY_state_Callback(const std_msgs::UInt16& state_msg);
        void blackout(int a);
        void getready_Callback(const std_msgs::UInt16& ready);
        void Front_ImageCb(const sensor_msgs::ImageConstPtr& msg);
        //Arm
        void Arm_status_Callback(const std_msgs::UInt16& state_msg);
        void Arm_joy_status_Callback(const std_msgs::UInt16& state_msg);
        void Arm_key_status_Callback(const std_msgs::UInt16& state_msg);
        void Arm_service_status_Callback(const std_msgs::UInt16& state_msg);


	/*********************
	** Logging
	**********************/
	enum LogLevel {
	         Debug,
	         Info,
	         Warn,
	         Error,
	         Fatal
	 };

	QStringListModel* loggingModel() { return &logging_model; }
	void log( const LogLevel &level, const std::string &msg);

Q_SIGNALS:
	void loggingUpdated();
    void rosShutdown();

    void statusUpdated();

private:
	int init_argc;
	char** init_argv;
        ros::Publisher mission_publisher;

        ros::Subscriber get_Ready_subscriber;

        ros::Subscriber A_state_subscriber;
        ros::Subscriber D_state_subscriber;
        ros::Subscriber O_state_subscriber;
        ros::Subscriber S_state_subscriber;
        ros::Subscriber P_state_subscriber;
        ros::Subscriber MD_state_subscriber;
        ros::Subscriber JOY_state_subscriber;
        ros::Subscriber Front_Image_subscriber;
        //image_transport::Subscriber Front_Image_subscriber2;

        ros::Subscriber Arm_status_subscriber;
        ros::Subscriber Arm_joy_status_subscriber;
        ros::Subscriber Arm_key_status_subscriber;
        ros::Subscriber Arm_service_status_subscriber;

        QStringListModel logging_model;
};

}  // namespace launchgui

#endif /* launchgui_QNODE_HPP_ */
