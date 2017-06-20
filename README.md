# Overview

Repository contains simulation software developed for "*Synchronization-free TDoA localization method for large scale wireless networks*" paper submitted to [Indoor Positioning and Indoor Navigation 2017 Conference][1]. Software consists OMNET++ simulation models and Matlab scripts for data analysis. Software is capable of simulation mobile node localization in various configuration discussed in article (different hardware clocks, various infrastructure node deployments etc.). 

Simulation uses modified [imperfect clock model for OMNET++][2] created by Jens Steinhauser.

# Running simulation

Individual simulation scenarios can be run using OMNET++ IDE. Simulations can be run in batch mode using helper scripts (`run`*SimulationCase*`.sh`) in `simulation` directory. Each simulation stores results in single CSV file in `simulations` directory. Name of that file depends on simulation scenario, for details refer to `simulations/ipin.ini`.

[1]: http://www.ipin2017.org/
[2]: https://github.com/JenSte/omnet-ptp
