# Overview

Repository contains simulation software developed for "*Synchronization-free TDoA localization method for large scale wireless networks*" paper submitted to [Indoor Positioning and Indoor Navigation 2017 Conference][1]. Software consists OMNET++ simulation models and Matlab scripts for data analysis. Software is capable of simulation mobile node localization in various configuration discussed in article (different hardware clocks, various infrastructure node deployments etc.). 

Simulation uses modified [imperfect clock model for OMNET++][2] created by Jens Steinhauser.

# Running simulation

Simulations can be run using OMNET++ IDE or in command line using helper scripts from `simulation` directory.

[1]: http://www.ipin2017.org/
[2]: https://github.com/JenSte/omnet-ptp
