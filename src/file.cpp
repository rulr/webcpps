#include <Poco/File.h>
#include <Poco/DateTimeParser.h>
#include <Poco/DateTime.h>
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeFormatter.h>
#include <Poco/NumericString.h>
#include <Poco/NumberFormatter.h>
#include <Poco/NumberParser.h>
#include "file.hpp"

namespace webcpp {

	file::file(const std::string& path, const std::string& type, Poco::Net::HTTPServerResponse::HTTPStatus status, unsigned expires)
	: filePath(path),
	mimeType(type),
	resStatus(status),
	expires(expires) {

	}

	void file::handleRequest(Poco::Net::HTTPServerRequest& req, Poco::Net::HTTPServerResponse& res) {

		Poco::DateTime dt;
		int tz;
		if (req.has("If-Modified-Since")) {
			Poco::DateTimeParser::parse(Poco::DateTimeFormat::HTTP_FORMAT, req.get("If-Modified-Since"), dt, tz);
			if (Poco::File(this->filePath).getLastModified() == dt.timestamp()) {
				this->resStatus = Poco::Net::HTTPServerResponse::HTTP_NOT_MODIFIED;
				res.set("Last-Modified", Poco::DateTimeFormatter::format(dt, Poco::DateTimeFormat::HTTP_FORMAT, tz));
			}
		}

		res.setChunkedTransferEncoding(true);
		res.set("Cache-Control", "max-age=" + Poco::NumberFormatter::format(this->expires));
		res.add("Cache-Control", "must-revalidate");

		if (this->resStatus != Poco::Net::HTTPServerResponse::HTTP_OK) {
			res.setStatusAndReason(resStatus);
		}
		res.sendFile(this->filePath, this->mimeType);
	}

}
