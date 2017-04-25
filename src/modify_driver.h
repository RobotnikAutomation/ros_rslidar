
#ifndef _MODIFY_DRIVER_H
#define _MODIFY_DRIVER_H

#include <string>
#include <ros/ros.h>
#include <diagnostic_updater/diagnostic_updater.h>
#include <diagnostic_updater/publisher.h>
#include <dynamic_reconfigure/server.h>
#include <rslidar/rslidarNodeConfig.h>
#include "myparam.h"
#include "convert_fullscan.h"
#include "input.h"

namespace rslidar_driver
{

class rslidarDriver
{
public:

  rslidarDriver(ros::NodeHandle node,
                 ros::NodeHandle private_nh);
  ~rslidarDriver() {}

  bool poll(void);

private:

  ///Callback for dynamic reconfigure
  void callback(rslidar::rslidarNodeConfig &config,
              uint32_t level);

  ///Pointer to dynamic reconfigure service srv_
  boost::shared_ptr<dynamic_reconfigure::Server<rslidar::
              rslidarNodeConfig> > srv_;

  // configuration parameters
  struct
  {
    std::string frame_id;            ///< tf frame ID
    std::string model;               ///< device model name
    int    npackets;                 ///< number of packets to collect
    double rpm;                      ///< device rotation rate (RPMs)
    double time_offset;              ///< time in seconds added to each  time stamp
  } config_;

  boost::shared_ptr<Input> input_;
  ros::Publisher output_;

  /** diagnostics updater */
  diagnostic_updater::Updater diagnostics_;
  double diag_min_freq_;
  double diag_max_freq_;
  boost::shared_ptr<diagnostic_updater::TopicDiagnostic> diag_topic_;
};

}

#endif
