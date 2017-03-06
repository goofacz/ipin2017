function [beacons, beaconEchos, rangingReplies, rangingReplyEchos] = loadSimulationResults()
beacons = csvread('beacons_result');
beaconEchos = csvread('beacon_echos_result');
rangingReplies = csvread('ranging_replies_result');
rangingReplyEchos = csvread('ranging_reply_echos_result');
end

