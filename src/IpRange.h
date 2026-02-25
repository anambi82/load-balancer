/**
 * @file IpRange.h
 * @brief Declaration of the IpRange class for representing and querying IPv4 address ranges.
 */

#ifndef IPRANGE_H
#define IPRANGE_H

#include <string>

/**
 * @class IpRange
 * @brief Represents an inclusive range of IPv4 addresses used for IP blocking.
 *
 * Converts IPv4 addresses to numeric form for efficient range comparisons.
 * Used by the LoadBalancer to reject requests whose source IP falls within
 * a blocked range.
 */
class IpRange{
    private:
        std::string startIp;  ///< Lower bound of the IP range (inclusive)
        std::string endIp;    ///< Upper bound of the IP range (inclusive)

        /**
         * @brief Converts a dotted-decimal IPv4 string to a 32-bit numeric value.
         * @param ip IPv4 address string in "a.b.c.d" format.
         * @return Numeric representation of the IP address.
         */
        long ipToNum(const std::string& ip) const;

    public:
        /**
         * @brief Constructs an IpRange with the given start and end addresses.
         * @param startIp Lower bound of the range (inclusive), in "a.b.c.d" format.
         * @param endIp Upper bound of the range (inclusive), in "a.b.c.d" format.
         */
        IpRange(const std::string& startIp, const std::string& endIp);

        /**
         * @brief Checks whether the given IP address falls within this range.
         * @param ip IPv4 address to test, in "a.b.c.d" format.
         * @return true if ip is within [startIp, endIp], false otherwise.
         */
        bool contains(const std::string& ip) const;

        /**
         * @brief Returns the lower bound of the IP range.
         * @return Start IP address string.
         */
        std::string getStartIp() const;

        /**
         * @brief Returns the upper bound of the IP range.
         * @return End IP address string.
         */
        std::string getEndIp() const;
};

#endif
