#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServer.h>
#include <Poco/File.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include "factory.hpp"
#include "error.hpp"
#include "file.hpp"
#include "mime.hpp"

namespace webcpp {

	factory::factory(webcpp::conf& conf) :
	mime(),
	root(conf.getString("root", "/var/www")),
	expires(conf.getUInt("expires", 3600)),
	err404page(conf.getString("err404", "err404.html")) {

	}

	Poco::Net::HTTPRequestHandler* factory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
		std::string uri = Poco::URI(request.getURI()).getPath();
		if (uri == "/" || uri.empty()) {
			uri = "/index.html";
		}

		Poco::File staticFile(this->root + uri);
		if (staticFile.exists()) {
			if (staticFile.isDirectory()) {
				return new webcpp::error(Poco::Net::HTTPServerResponse::HTTP_INTERNAL_SERVER_ERROR);
			}
			if (staticFile.isFile()) {
				return new webcpp::file(staticFile.path(), this->mime.getType(Poco::Path(staticFile.path()).getExtension()), Poco::Net::HTTPServerResponse::HTTP_OK, this->expires);
			}
		}

		Poco::Path err404(this->root + "/" + this->err404page);
		if (Poco::File(err404).exists()) {
			return new webcpp::file(err404.toString(), this->mime.getType(err404.getExtension()), Poco::Net::HTTPServerResponse::HTTP_MOVED_PERMANENTLY);
		}
		return new webcpp::error(Poco::Net::HTTPServerResponse::HTTP_NOT_FOUND);
	}

}