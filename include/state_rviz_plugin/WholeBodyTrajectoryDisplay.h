///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (C) 2020, University of Edinburgh, Istituto Italiano di Tecnologia
// Copyright note valid unless otherwise stated in individual files.
// All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#ifndef STATE_RVIZ_PLUGIN_WHOLE_BODY_TRAJECTORY_DISPLAY_H
#define STATE_RVIZ_PLUGIN_WHOLE_BODY_TRAJECTORY_DISPLAY_H

#include <pinocchio/parsers/urdf.hpp>
#include <pinocchio/algorithm/center-of-mass.hpp>

#include <rviz/message_filter_display.h>
#include <rviz/robot/robot.h>
#include <state_msgs/WholeBodyTrajectory.h>
#include <state_rviz_plugin/PointVisual.h>
#include <state_rviz_plugin/ArrowVisual.h>
#include <state_rviz_plugin/PinocchioLinkUpdater.h>

namespace Ogre {
class ManualObject;
}

namespace rviz {

class ColorProperty;
class FloatProperty;
class IntProperty;
class EnumProperty;
class BillboardLine;
class VectorProperty;
class Axes;

} // namespace rviz

namespace state_rviz_plugin {

/**
 * @class WholeBodyTrajectoryDisplay
 * @brief Displays a state_msgs::WholeBodyTrajectory message
 */
class WholeBodyTrajectoryDisplay
    : public rviz::MessageFilterDisplay<state_msgs::WholeBodyTrajectory> {
  Q_OBJECT
public:
  /** @brief Constructor function */
  WholeBodyTrajectoryDisplay();

  /** @brief Destructor function */
  ~WholeBodyTrajectoryDisplay();

  /** @brief Clear the visuals by deleting their objects */
  void reset() override;

  /** @brief Overridden from Display. */
  void onInitialize() override;

  void onEnable() override;

  void onDisable() override;

  /** @brief Called when the fixed frame changed */
  void fixedFrameChanged();

  /**
   * @brief Function to handle an incoming ROS message
   * This is our callback to handle an incoming message
   * @param const state_msgs::WholeBodyTrajectory::ConstPtr& Whole-body
   * trajectory msg
   */
  void processMessage(const state_msgs::WholeBodyTrajectory::ConstPtr &msg);

private Q_SLOTS:
  /** @brief Helper function to apply color and alpha to all visuals.
   * Set the current color and alpha values for each visual */
  void updateTargetEnable();
  void updateRobotDescription();
  void updateRobotVisualVisible();
  void updateRobotCollisionVisible();
  void updateRobotAlpha();
  void updateForceColorAndAlpha();
  void updateForceArrowGeometry();
  void updateCoMEnable();
  void updateCoMStyle();
  void updateCoMLineProperties();
  void updateContactEnable();
  void updateContactStyle();
  void updateContactLineProperties();
  void pushBackCoMAxes(const Ogre::Vector3 &axes_position,
                       const Ogre::Quaternion &axes_orientation);
  void pushBackContactAxes(const Ogre::Vector3 &axes_position,
                           const Ogre::Quaternion &axes_orientation);

private:
  /** @brief Process the trajectories */
  void processTargetPosture();
  void processCoMTrajectory();
  void processContactTrajectory();

  void loadRobotModel();
  void clearRobotModel();

  /** Destroy all the objects for visualization */
  void destroyObjects();

  /** @brief Whole-body trajectory message */
  state_msgs::WholeBodyTrajectory::ConstPtr msg_;

  /** @brief Indicates if it's been received a message */
  bool is_info_;

  /** @brief Properties to show on side panel */
  rviz::Property *target_category_;
  rviz::Property *com_category_;
  rviz::Property *contact_category_;

  /** @brief Object for visualization of the data */
  boost::shared_ptr<rviz::Robot> robot_;
  boost::shared_ptr<Ogre::ManualObject> com_manual_object_;
  boost::shared_ptr<rviz::BillboardLine> com_billboard_line_;
  std::vector<boost::shared_ptr<PointVisual>> com_points_;
  std::vector<boost::shared_ptr<rviz::Axes>> com_axes_;
  std::vector<boost::shared_ptr<Ogre::ManualObject>> contact_manual_object_;
  std::vector<boost::shared_ptr<rviz::BillboardLine>> contact_billboard_line_;
  std::vector<std::vector<boost::shared_ptr<PointVisual>>> contact_points_;
  std::vector<boost::shared_ptr<rviz::Axes>> contact_axes_;

  /** @brief Property objects for user-editable properties */
  rviz::BoolProperty *target_enable_property_;
  rviz::StringProperty* robot_description_property_;
  rviz::Property* robot_visual_enabled_property_;
  rviz::Property* robot_collision_enabled_property_;
  rviz::FloatProperty* robot_alpha_property_;
  std::vector<boost::shared_ptr<ArrowVisual>> force_visual_;
  rviz::BoolProperty *force_enable_property_;
  rviz::ColorProperty *force_color_property_;
  rviz::FloatProperty *force_alpha_property_;
  rviz::FloatProperty *force_head_radius_property_;
  rviz::FloatProperty *force_head_length_property_;
  rviz::FloatProperty *force_shaft_radius_property_;
  rviz::FloatProperty *force_shaft_length_property_;

  rviz::BoolProperty *com_enable_property_;
  rviz::EnumProperty *com_style_property_;
  rviz::ColorProperty *com_color_property_;
  rviz::FloatProperty *com_alpha_property_;
  rviz::FloatProperty *com_line_width_property_;
  rviz::FloatProperty *com_scale_property_;

  rviz::BoolProperty *contact_enable_property_;
  rviz::EnumProperty *contact_style_property_;
  rviz::ColorProperty *contact_color_property_;
  rviz::FloatProperty *contact_alpha_property_;
  rviz::FloatProperty *contact_line_width_property_;
  rviz::FloatProperty *contact_scale_property_;

  Ogre::Vector3 last_point_position_;

  enum LineStyle { BILLBOARDS, LINES, POINTS };

  std::string robot_description_;
  pinocchio::Model model_;
  pinocchio::Data data_;
  double weight_;
  bool target_enable_;     //!< Flag that indicates if the target visualization is enable
  bool com_enable_;     //!< Flag that indicates if the CoM visualization is enable
  bool com_axes_enable_;     //!< Flag that indicates if the CoM axes visualization is enable
  bool contact_enable_; //!< Flag that indicates if the contact visualization is enable
  bool contact_axes_enable_; //!< Flag that indicates if the contact axes visualization is enable
};

} // namespace state_rviz_plugin

#endif // STATE_RVIZ_PLUGIN_WHOLE_BODY_TRAJECTORY_DISPLAY_H
