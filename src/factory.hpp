#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Logger.h>
#include <Poco/Path.h>

#include "mime.hpp"
#include "conf.hpp"

namespace webcpp {

	class factory : public Poco::Net::HTTPRequestHandlerFactory {
	public:
		factory(webcpp::conf& conf);
		Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request);
	private:
		webcpp::mime mime;
		const std::string root;
		const std::string err404page;
		const unsigned expires;
	};
}
#endif /* FACTORY_HPP */

