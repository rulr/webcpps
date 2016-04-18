#ifndef FILE_HPP
#define FILE_HPP

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <string>

namespace webcpp {

	class file : public Poco::Net::HTTPRequestHandler {
	public:
		file(const std::string &path, const std::string &type, Poco::Net::HTTPServerResponse::HTTPStatus status = Poco::Net::HTTPServerResponse::HTTP_OK, unsigned expires = 3600);
		void handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res);
	private:
		const std::string filePath;
		const std::string mimeType;
		Poco::Net::HTTPServerResponse::HTTPStatus resStatus;
		unsigned expires;
	};
}
#endif /* FILE_HPP */

