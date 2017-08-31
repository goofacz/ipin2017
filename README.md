# Overview

Repository provides simulation software developed for "*Synchronization-free TDoA localization method for large scale wireless networks*" paper submitted to [Indoor Positioning and Indoor Navigation 2017 Conference][1]. Software consists OMNET++ simulation models and Matlab scripts for data analysis. Software is capable of simulating mobile node localization in various configurations discussed in article (different hardware clocks, various infrastructure node deployments, stationary and moving mobile nodes etc.).

Simulation uses modified [imperfect hardware clock model for OMNET++][3] created by Jens Steinhauser.

# Setup

* Download and install OMNET++ 5.0 and INET 3.4.0 on your platform.
* Checkout and import this project into OMNET++.

# Running simulation

Individual simulation scenarios can be run using OMNET++ IDE in GUI mode and in command line using OMNET++ utility tools like `opp_run` and `opp_run`. Simulations can be run in parallel using helper scripts (`run`*SimulationCase*`.sh`) in `simulation` directory. Each simulation stores results in single CSV file in `simulations` directory. Name of that file depends on simulation scenario, for details refer to `simulations/ipin.ini`.

[1]: http://www.ipin2017.org/
[2]: https://www.omnetpp.org/
[3]: https://github.com/JenSte/omnet-ptp

# Author
Tomasz Jankowski <tomasz.jankowski AT pwr.edu.pl>


