#include "mitkPluginActivator.h"

#include "QmitkSegmentationView.h"
#include "QmitkThresholdAction.h"
#include "QmitkCreatePolygonModelAction.h"
#include "QmitkStatisticsAction.h"
#include "QmitkAutocropAction.h"
#include "QmitkSegmentationPreferencePage.h"

using namespace mitk;

void PluginActivator::start(ctkPluginContext *context)
{
  BERRY_REGISTER_EXTENSION_CLASS(QmitkSegmentationView, context);
  BERRY_REGISTER_EXTENSION_CLASS(QmitkThresholdAction, context);
  BERRY_REGISTER_EXTENSION_CLASS(QmitkCreatePolygonModelAction, context);
  BERRY_REGISTER_EXTENSION_CLASS(QmitkStatisticsAction, context);
  BERRY_REGISTER_EXTENSION_CLASS(QmitkAutocropAction, context);
  BERRY_REGISTER_EXTENSION_CLASS(QmitkSegmentationPreferencePage, context);
}

void PluginActivator::stop(ctkPluginContext *)
{
}

Q_EXPORT_PLUGIN2(org_mitk_gui_qt_segmentation, mitk::PluginActivator)
