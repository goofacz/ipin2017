# Introduction

Repository provides simulation software developed for "*Synchronization-free TDoA localization method for large scale wireless networks*" paper submitted to [Indoor Positioning and Indoor Navigation 2017 Conference][1]. Software consists OMNET++ simulation models and Matlab scripts for data analysis. Software is capable of simulating mobile node localization in various configurations discussed in article (different hardware clocks, various infrastructure node deployments, stationary and moving mobile nodes etc.).

Simulation uses modified [imperfect hardware clock model for OMNET++][3] created by Jens Steinhauser.

# Prerequisites

* OMNET++ 5.0 with INET 3.4.0 on any supported platform
* Familiarity with OMNET++ (running and developing simulation).

# Repository structure

Brief description of directories and files in repository

* `src` directory

   * Definitions of main simulation components such as: mobile and anchor nodes, ranging applications, hardware clocks etc. written in C++ and NED languages.
   
* `simulations` directory

   * `MovingNetwork.ned` and `StationaryNetwork.ned` files define artificial simulation areas for moving and stationary mobile node respectively. 
   * `ipin.ini` defines all simulation cases (number of nodes, speed, hardware clock precision etc.).
   * Bash scripts (prefixed with `run`) running various sets of simulations in parallel.

* `matlab`

   * Matlab scripts for data analysis.

# Components

OMNET++ is a component-based simulation environment, therefore simulations are composed of complex component structures. Such components represent various entities (e.g. wireless nodes) and implement simulation logic.

Components hierarchy:

* `IHardwareClock`

   Common interface for all hardware clocks
   
   * `HardwareClock`
   
      Common base hardware clock representation.
      
      * `NoneDrift`
      
         Perfect hardware clock without any drift.
         
      * `ConstantDrift`
      * `BoundedDrift`
      * `BoundedDriftVariation`
      
         Various hardware clocks with different drifts as described in [Jens Steinhauser's paper][3].
         
* `IRangingApplication`

   Common interface for ranging applications running on wireless nodes.
   
   * `RangingApplication`
   
     Common base component for all ranging applications regardless of particular localization method.
     
     * `TDoAAnchorRangingApplication`
     * `TDoAMobileRangingApplication`
     
     Ranging application implementing logic required by proposed localization method.
   
* `RangingHost`

   RadioHost extends INET's `MobileHost` component and represents a freestanding wireless node. It includes and interconnects three basic sub components: hardware clock, ranging application and network interface. By design RadioHost is highly configurable, e.g. it is possible to define a ranging hist running `TDoAAnchorRangingApplication` application and freely exchange hardware clocks.

There are also number of `*.msg` files defining radio frames.

# First steps

1. Checkout this repository and import it in OMNET++,
2. Build & Run simulation in GUI mode.
3. Simulator windows should show up in a moment. In a simulator's pop-up dialog choose *TDoA_moving_perfect_clock* configuration and run no. 0.
4. Proceed with simulation and close simulator when it is done.
5. A CSV file with simulation results will appear in `simulations` directory. The file name will correspond to simulation case configuration (it will include information about initial node position, speed, used clock etc.). In this case file should be named `tdoa_perf_1mps_0deg_100m_100m` - mobile node was equipped with perfect clock and was moving from initial position (100m, 100m) at constant speed (1m/s). For more details regarding file name convention refer to documentation in `analyzeMovingNode.m`.
6. Analyze simulation results in Matlab using following scripts: `analyzeMovingNode.m` for moving mobile nodes and `analyzeStationaryNode.m` for stationary mobile nodes. In this case run `analyzeMovingNode.m` with following arguments:

   `>> [approxPos, realPos, absPosErrs, absErrStats]=analyzeMovingNode('../simulations', 'tdoa', 100, 100, 1, 0);`

[1]: http://www.ipin2017.org/
[2]: https://www.omnetpp.org/
[3]: https://github.com/JenSte/omnet-ptp

# Author
Tomasz Jankowski <t.jankowski AT pwr.edu.pl>
