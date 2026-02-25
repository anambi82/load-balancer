/**
 * @file Request.h
 * @brief Declaration of the Request class representing a single network request.
 */

#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**
 * @class Request
 * @brief Represents a single network request routed through the load balancer.
 *
 * Stores the source IP, destination IP, estimated processing time, and job type
 * ('P' for processing, 'S' for streaming). Also provides static factory methods
 * for generating random requests and IPs.
 */
class Request{
    private:
        std::string ipIn;      ///< Source IP address of the request
        std::string ipOut;     ///< Destination IP address of the request
        int processTime;       ///< Number of clock cycles required to process this request
        char jobType;          ///< Job type: 'P' (processing) or 'S' (streaming)
    public:
        /**
         * @brief Default constructor. Initializes all fields to zero/default values.
         */
        Request();

        /**
         * @brief Constructs a Request with explicit field values.
         * @param ipIn Source IP address.
         * @param ipOut Destination IP address.
         * @param processTime Number of clock cycles to process this request.
         * @param jobType Job type character ('P' or 'S').
         */
        Request(std::string ipIn, std::string ipOut, int processTime, char jobType);

        /**
         * @brief Returns the source IP address.
         * @return Source IP as a string.
         */
        std::string getIpIn() const;

        /**
         * @brief Returns the destination IP address.
         * @return Destination IP as a string.
         */
        std::string getIpOut() const;

        /**
         * @brief Returns the processing time in clock cycles.
         * @return Processing time.
         */
        int getProcessTime() const;

        /**
         * @brief Returns the job type character.
         * @return 'P' for processing or 'S' for streaming.
         */
        char getJobType() const;

        /**
         * @brief Generates a random IPv4 address string.
         * @return A randomly generated IP address in "a.b.c.d" format.
         */
        static std::string generateRandomIp();

        /**
         * @brief Generates a Request with random source/destination IPs and a random process time.
         * @param minTime Minimum processing time (inclusive).
         * @param maxTime Maximum processing time (inclusive).
         * @return A randomly generated Request object.
         */
        static Request generateRandomRequest(int minTime, int maxTime);
};

#endif
