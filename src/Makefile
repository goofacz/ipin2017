#
# OMNeT++/OMNEST Makefile for ipin2017
#
# This file was generated with the command:
#  opp_makemake -f --deep -I../../inet/src/inet/linklayer/common -I../../inet/src -I../../inet/src/inet/physicallayer/contract/packetlevel -I../../inet/src/inet/common/geometry/common -I../../inet/src/inet/common -I../../inet/src/inet/linklayer/ideal -I../../inet/src/inet/physicallayer/common/packetlevel -L../../inet/out/$$\(CONFIGNAME\)/src -lINET -KINET_PROJ=../../inet
#

# Name of target to be created (-o option)
TARGET = ipin2017$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(QTENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)
#USERIF_LIBS = $(QTENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I../../inet/src/inet/linklayer/common \
    -I../../inet/src \
    -I../../inet/src/inet/physicallayer/contract/packetlevel \
    -I../../inet/src/inet/common/geometry/common \
    -I../../inet/src/inet/common \
    -I../../inet/src/inet/linklayer/ideal \
    -I../../inet/src/inet/physicallayer/common/packetlevel \
    -I.

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS = -L../../inet/out/$(CONFIGNAME)/src  -lINET
LIBS += -Wl,-rpath,`abspath ../../inet/out/$(CONFIGNAME)/src`

# Output directory
PROJECT_OUTPUT_DIR = ../out
PROJECTRELATIVE_PATH = src
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cc, .msg and .sm files
OBJS = \
    $O/RangingApplication.o \
    $O/RangingHost.o \
    $O/TDoAMobileRangingApplication.o \
    $O/BackhaulMessage.o \
    $O/MobileRangingApplication.o \
    $O/HelperAnchorRangingApplication.o \
    $O/TDoAAnchorRangingApplication.o \
    $O/MasterAnchorRangingApplication.o \
    $O/Frame_m.o \
    $O/BeaconFrame_m.o \
    $O/TDoAAnchorSelfMessage_m.o \
    $O/BackhaulMessage_m.o \
    $O/MasterAnchorSelfMessage_m.o \
    $O/RangingReplyFrame_m.o

# Message files
MSGFILES = \
    Frame.msg \
    BeaconFrame.msg \
    TDoAAnchorSelfMessage.msg \
    BackhaulMessage.msg \
    MasterAnchorSelfMessage.msg \
    RangingReplyFrame.msg

# SM files
SMFILES =

# Other makefile variables (-K)
INET_PROJ=../../inet

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)
SMCOPTS =

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders smheaders

.SUFFIXES: .cc

$O/%.o: %.cc $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cc %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cc $(MSGCOPTS) $?

%_sm.cc %_sm.h: %.sm
	$(qecho) SMC: $<
	$(Q)$(SMC) -c++ -suffix cc $(SMCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

smheaders: $(SMFILES:.sm=_sm.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f ipin2017 ipin2017.exe libipin2017.so libipin2017.a libipin2017.dll libipin2017.dylib
	$(Q)-rm -f ./*_m.cc ./*_m.h ./*_sm.cc ./*_sm.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES) $(SM_CC_FILES)  ./*.cc

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/BackhaulMessage.o: BackhaulMessage.cc \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/INETMath.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/geometry/common/Coord.h \
	$(INET_PROJ)/src/inet/features.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	BackhaulMessage.h \
	BackhaulMessage_m.h \
	Frame_m.h
$O/BackhaulMessage_m.o: BackhaulMessage_m.cc \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/INETMath.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/geometry/common/Coord.h \
	$(INET_PROJ)/src/inet/features.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	BackhaulMessage_m.h \
	Frame_m.h
$O/BeaconFrame_m.o: BeaconFrame_m.cc \
	BeaconFrame_m.h \
	Frame_m.h
$O/Frame_m.o: Frame_m.cc \
	Frame_m.h
$O/HelperAnchorRangingApplication.o: HelperAnchorRangingApplication.cc \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/INETMath.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/Units.h \
	$(INET_PROJ)/src/inet/common/geometry/common/Coord.h \
	$(INET_PROJ)/src/inet/common/geometry/common/EulerAngles.h \
	$(INET_PROJ)/src/inet/common/mapping/Interpolation.h \
	$(INET_PROJ)/src/inet/common/mapping/MappingBase.h \
	$(INET_PROJ)/src/inet/common/mapping/MappingUtils.h \
	$(INET_PROJ)/src/inet/features.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/mobility/contract/IMobility.h \
	$(INET_PROJ)/src/inet/physicallayer/base/packetlevel/PhysicalLayerDefs.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/bitlevel/ISignalAnalogModel.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IAntenna.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IArrival.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IInterference.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IListening.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IListeningDecision.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IModulation.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/INoise.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPhysicalLayer.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPhysicalLayerFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPrintableObject.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadio.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioSignal.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceiver.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReception.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceptionDecision.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceptionResult.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ISNIR.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ITransmission.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ITransmitter.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/RadioControlInfo_m.h \
	BackhaulMessage.h \
	BackhaulMessage_m.h \
	BeaconFrame_m.h \
	Frame_m.h \
	HelperAnchorRangingApplication.h \
	Listener.h \
	RangingApplication.h \
	RangingHost.h \
	RangingReplyFrame_m.h
$O/MasterAnchorRangingApplication.o: MasterAnchorRangingApplication.cc \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/INETMath.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/Units.h \
	$(INET_PROJ)/src/inet/common/geometry/common/Coord.h \
	$(INET_PROJ)/src/inet/common/geometry/common/EulerAngles.h \
	$(INET_PROJ)/src/inet/common/mapping/Interpolation.h \
	$(INET_PROJ)/src/inet/common/mapping/MappingBase.h \
	$(INET_PROJ)/src/inet/common/mapping/MappingUtils.h \
	$(INET_PROJ)/src/inet/features.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/linklayer/ideal/IdealMacFrame_m.h \
	$(INET_PROJ)/src/inet/mobility/contract/IMobility.h \
	$(INET_PROJ)/src/inet/physicallayer/base/packetlevel/PhysicalLayerDefs.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/bitlevel/ISignalAnalogModel.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IAntenna.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IArrival.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IInterference.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IListening.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IListeningDecision.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IModulation.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/INoise.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPhysicalLayer.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPhysicalLayerFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPrintableObject.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadio.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioSignal.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceiver.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReception.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceptionDecision.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceptionResult.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ISNIR.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ITransmission.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ITransmitter.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/RadioControlInfo_m.h \
	BackhaulMessage.h \
	BackhaulMessage_m.h \
	BeaconFrame_m.h \
	Frame_m.h \
	Listener.h \
	MasterAnchorRangingApplication.h \
	MasterAnchorSelfMessage_m.h \
	Ranging.h \
	RangingApplication.h \
	RangingHost.h \
	RangingReplyFrame_m.h \
	Utilities.h
$O/MasterAnchorSelfMessage_m.o: MasterAnchorSelfMessage_m.cc \
	MasterAnchorSelfMessage_m.h
$O/MobileRangingApplication.o: MobileRangingApplication.cc \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/INETMath.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/Units.h \
	$(INET_PROJ)/src/inet/common/geometry/common/Coord.h \
	$(INET_PROJ)/src/inet/common/geometry/common/EulerAngles.h \
	$(INET_PROJ)/src/inet/common/mapping/Interpolation.h \
	$(INET_PROJ)/src/inet/common/mapping/MappingBase.h \
	$(INET_PROJ)/src/inet/common/mapping/MappingUtils.h \
	$(INET_PROJ)/src/inet/features.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/linklayer/ideal/IdealMacFrame_m.h \
	$(INET_PROJ)/src/inet/mobility/contract/IMobility.h \
	$(INET_PROJ)/src/inet/physicallayer/base/packetlevel/PhysicalLayerDefs.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/bitlevel/ISignalAnalogModel.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IAntenna.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IArrival.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IInterference.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IListening.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IListeningDecision.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IModulation.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/INoise.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPhysicalLayer.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPhysicalLayerFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPrintableObject.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadio.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioSignal.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceiver.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReception.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceptionDecision.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceptionResult.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ISNIR.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ITransmission.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ITransmitter.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/RadioControlInfo_m.h \
	BeaconFrame_m.h \
	Frame_m.h \
	Listener.h \
	MobileRangingApplication.h \
	RangingApplication.h \
	RangingHost.h \
	RangingReplyFrame_m.h \
	Utilities.h
$O/RangingApplication.o: RangingApplication.cc \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/INETMath.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/Units.h \
	$(INET_PROJ)/src/inet/common/geometry/common/Coord.h \
	$(INET_PROJ)/src/inet/common/geometry/common/EulerAngles.h \
	$(INET_PROJ)/src/inet/common/mapping/Interpolation.h \
	$(INET_PROJ)/src/inet/common/mapping/MappingBase.h \
	$(INET_PROJ)/src/inet/common/mapping/MappingUtils.h \
	$(INET_PROJ)/src/inet/features.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/mobility/contract/IMobility.h \
	$(INET_PROJ)/src/inet/physicallayer/base/packetlevel/PhysicalLayerDefs.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/bitlevel/ISignalAnalogModel.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IAntenna.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IArrival.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IInterference.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IListening.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IListeningDecision.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IModulation.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/INoise.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPhysicalLayer.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPhysicalLayerFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPrintableObject.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadio.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioSignal.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceiver.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReception.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceptionDecision.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceptionResult.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ISNIR.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ITransmission.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ITransmitter.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/RadioControlInfo_m.h \
	Frame_m.h \
	Listener.h \
	RangingApplication.h \
	RangingHost.h
$O/RangingHost.o: RangingHost.cc \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/INETMath.h \
	$(INET_PROJ)/src/inet/common/IVisitor.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/IntervalTree.h \
	$(INET_PROJ)/src/inet/common/Units.h \
	$(INET_PROJ)/src/inet/common/geometry/base/GeometricObjectBase.h \
	$(INET_PROJ)/src/inet/common/geometry/base/ShapeBase.h \
	$(INET_PROJ)/src/inet/common/geometry/common/Coord.h \
	$(INET_PROJ)/src/inet/common/geometry/common/EulerAngles.h \
	$(INET_PROJ)/src/inet/common/geometry/common/Rotation.h \
	$(INET_PROJ)/src/inet/common/geometry/object/LineSegment.h \
	$(INET_PROJ)/src/inet/common/lifecycle/ILifecycle.h \
	$(INET_PROJ)/src/inet/common/lifecycle/LifecycleOperation.h \
	$(INET_PROJ)/src/inet/common/lifecycle/NodeOperations.h \
	$(INET_PROJ)/src/inet/common/lifecycle/OperationalBase.h \
	$(INET_PROJ)/src/inet/common/mapping/Interpolation.h \
	$(INET_PROJ)/src/inet/common/mapping/MappingBase.h \
	$(INET_PROJ)/src/inet/common/mapping/MappingUtils.h \
	$(INET_PROJ)/src/inet/environment/common/Material.h \
	$(INET_PROJ)/src/inet/environment/contract/IGround.h \
	$(INET_PROJ)/src/inet/environment/contract/IMaterial.h \
	$(INET_PROJ)/src/inet/environment/contract/IMaterialRegistry.h \
	$(INET_PROJ)/src/inet/environment/contract/IObjectCache.h \
	$(INET_PROJ)/src/inet/environment/contract/IPhysicalEnvironment.h \
	$(INET_PROJ)/src/inet/environment/contract/IPhysicalObject.h \
	$(INET_PROJ)/src/inet/features.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/mobility/contract/IMobility.h \
	$(INET_PROJ)/src/inet/physicallayer/base/packetlevel/PhysicalLayerBase.h \
	$(INET_PROJ)/src/inet/physicallayer/base/packetlevel/PhysicalLayerDefs.h \
	$(INET_PROJ)/src/inet/physicallayer/common/packetlevel/Radio.h \
	$(INET_PROJ)/src/inet/physicallayer/common/packetlevel/RadioFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/bitlevel/ISignalAnalogModel.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IAnalogModel.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IAntenna.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IArrival.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IBackgroundNoise.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ICommunicationCache.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IInterference.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IListening.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IListeningDecision.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IMediumLimitCache.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IModulation.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/INeighborCache.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/INoise.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IObstacleLoss.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPathLoss.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPhysicalLayer.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPhysicalLayerFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPrintableObject.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPropagation.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadio.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioMedium.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioSignal.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceiver.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReception.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceptionDecision.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceptionResult.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ISNIR.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ITransmission.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ITransmitter.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/RadioControlInfo_m.h \
	Listener.h \
	RangingHost.h
$O/RangingReplyFrame_m.o: RangingReplyFrame_m.cc \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/INETMath.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/geometry/common/Coord.h \
	$(INET_PROJ)/src/inet/features.h \
	Frame_m.h \
	RangingReplyFrame_m.h
$O/TDoAAnchorRangingApplication.o: TDoAAnchorRangingApplication.cc \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/INETMath.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/Units.h \
	$(INET_PROJ)/src/inet/common/geometry/common/Coord.h \
	$(INET_PROJ)/src/inet/common/geometry/common/EulerAngles.h \
	$(INET_PROJ)/src/inet/common/mapping/Interpolation.h \
	$(INET_PROJ)/src/inet/common/mapping/MappingBase.h \
	$(INET_PROJ)/src/inet/common/mapping/MappingUtils.h \
	$(INET_PROJ)/src/inet/features.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/linklayer/ideal/IdealMacFrame_m.h \
	$(INET_PROJ)/src/inet/mobility/contract/IMobility.h \
	$(INET_PROJ)/src/inet/physicallayer/base/packetlevel/PhysicalLayerDefs.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/bitlevel/ISignalAnalogModel.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IAntenna.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IArrival.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IInterference.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IListening.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IListeningDecision.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IModulation.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/INoise.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPhysicalLayer.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPhysicalLayerFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPrintableObject.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadio.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioSignal.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceiver.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReception.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceptionDecision.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceptionResult.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ISNIR.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ITransmission.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ITransmitter.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/RadioControlInfo_m.h \
	BeaconFrame_m.h \
	Frame_m.h \
	Listener.h \
	Ranging.h \
	RangingApplication.h \
	RangingHost.h \
	TDoAAnchorRangingApplication.h \
	TDoAAnchorSelfMessage_m.h \
	Utilities.h
$O/TDoAAnchorSelfMessage_m.o: TDoAAnchorSelfMessage_m.cc \
	TDoAAnchorSelfMessage_m.h
$O/TDoAMobileRangingApplication.o: TDoAMobileRangingApplication.cc \
	$(INET_PROJ)/src/inet/common/Compat.h \
	$(INET_PROJ)/src/inet/common/INETDefs.h \
	$(INET_PROJ)/src/inet/common/INETMath.h \
	$(INET_PROJ)/src/inet/common/InitStages.h \
	$(INET_PROJ)/src/inet/common/Units.h \
	$(INET_PROJ)/src/inet/common/geometry/common/Coord.h \
	$(INET_PROJ)/src/inet/common/geometry/common/EulerAngles.h \
	$(INET_PROJ)/src/inet/common/mapping/Interpolation.h \
	$(INET_PROJ)/src/inet/common/mapping/MappingBase.h \
	$(INET_PROJ)/src/inet/common/mapping/MappingUtils.h \
	$(INET_PROJ)/src/inet/features.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl.h \
	$(INET_PROJ)/src/inet/linklayer/common/Ieee802Ctrl_m.h \
	$(INET_PROJ)/src/inet/linklayer/common/MACAddress.h \
	$(INET_PROJ)/src/inet/linklayer/contract/IMACProtocolControlInfo.h \
	$(INET_PROJ)/src/inet/linklayer/ideal/IdealMacFrame_m.h \
	$(INET_PROJ)/src/inet/mobility/contract/IMobility.h \
	$(INET_PROJ)/src/inet/physicallayer/base/packetlevel/PhysicalLayerDefs.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/bitlevel/ISignalAnalogModel.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IAntenna.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IArrival.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IInterference.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IListening.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IListeningDecision.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IModulation.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/INoise.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPhysicalLayer.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPhysicalLayerFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IPrintableObject.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadio.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioFrame.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IRadioSignal.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceiver.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReception.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceptionDecision.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/IReceptionResult.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ISNIR.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ITransmission.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/ITransmitter.h \
	$(INET_PROJ)/src/inet/physicallayer/contract/packetlevel/RadioControlInfo_m.h \
	BeaconFrame_m.h \
	Frame_m.h \
	Listener.h \
	RangingApplication.h \
	RangingHost.h \
	TDoAMobileRangingApplication.h \
	Utilities.h

