/**
 * @file Config.h
 * @brief Declaration of the Config class for load balancer simulation settings.
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include "IpRange.h"

/**
 * @class Config
 * @brief Holds all configuration parameters for the load balancer simulation.
 *
 * Parameters can be loaded from a key=value config file or set to built-in
 * defaults. The LoadBalancer reads this object at startup to determine
 * initial server count, scaling thresholds, request probabilities, and
 * blocked IP ranges.
 */
class Config{
    private:
        int initServers;              ///< Number of servers to create at startup
        int totalRunTime;             ///< Total number of clock cycles to simulate
        int minQueuePerServer;        ///< Queue depth per server below which scale-down is triggered
        int maxQueuePerServer;        ///< Queue depth per server above which scale-up is triggered
        int scaleCooldownTime;        ///< Minimum clock cycles between consecutive scaling events
        int minProcessTime;           ///< Minimum processing time for a generated request (cycles)
        int maxProcessTime;           ///< Maximum processing time for a generated request (cycles)
        double newRequestProb;        ///< Probability [0,1] of a new request arriving each cycle
        std::vector<IpRange> blockedIpRanges;  ///< IP ranges whose requests will be rejected

        /**
         * @brief Parses a comma-separated list of "startIp-endIp" range strings.
         * @param rangesStr Comma-separated string of IP ranges (e.g. "10.0.0.0-10.0.0.255,192.168.1.0-192.168.1.100").
         */
        void parseBlockedIpRanges(const std::string& rangesStr);

        /**
         * @brief Initializes all fields to their built-in default values.
         */
        void setDefault();

    public:
        /**
         * @brief Default constructor. Calls setDefault() to initialize all fields.
         */
        Config();

        /**
         * @brief Loads configuration from a key=value text file.
         *
         * Lines starting with '#' and blank lines are ignored. If a key is
         * unrecognized, it is silently skipped.
         *
         * @param filename Path to the configuration file.
         * @return true if the file was opened and parsed successfully, false otherwise.
         */
        bool loadFromFile(const std::string& filename);

        /** @brief Returns the initial number of servers. */
        int getInitServers() const;

        /** @brief Returns the total simulation run time in clock cycles. */
        int getTotalRunTime() const;

        /** @brief Returns the per-server queue minimum threshold for scale-down. */
        int getMinQueuePerServer() const;

        /** @brief Returns the per-server queue maximum threshold for scale-up. */
        int getMaxQueuePerServer() const;

        /** @brief Returns the minimum clock cycles required between scaling events. */
        int getScaleCooldownTime() const;

        /** @brief Returns the minimum request processing time in clock cycles. */
        int getMinProcessTime() const;

        /** @brief Returns the maximum request processing time in clock cycles. */
        int getMaxProcessTime() const;

        /** @brief Returns the per-cycle probability of a new request arriving. */
        double getNewRequestProb() const;

        /**
         * @brief Returns a read-only reference to the list of blocked IP ranges.
         * @return Const reference to the blocked IP range vector.
         */
        const std::vector<IpRange>& getBlockedIpRanges() const;

        /**
         * @brief Overrides the initial server count (e.g., from user input).
         * @param count New initial server count.
         */
        void setInitServers(int count);

        /**
         * @brief Overrides the total simulation run time (e.g., from user input).
         * @param time New run time in clock cycles.
         */
        void setTotalRunTime(int time);

        /**
         * @brief Prints all current configuration values to standard output.
         */
        void printConfig() const;
};


#endif
