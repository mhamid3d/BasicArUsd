#include <iostream>
#include <string>

#include "pxr/pxr.h"
#include "pxr/usd/ar/defineResolver.h"
#include "pxr/usd/ar/assetInfo.h"
#include "pxr/usd/ar/resolverContext.h"

#include "pxr/base/arch/fileSystem.h"
#include "pxr/base/arch/systemInfo.h"
#include "pxr/base/tf/getenv.h"
#include "pxr/base/tf/fileUtils.h"
#include "pxr/base/tf/pathUtils.h"
#include "pxr/base/tf/staticData.h"
#include "pxr/base/tf/stringUtils.h"
#include "pxr/base/vt/value.h"

#include "tbb/concurrent_hash_map.h"

#include "basicResolver.h"

PXR_NAMESPACE_OPEN_SCOPE

AR_DEFINE_RESOLVER(BasicResolver, ArResolver);


BasicResolver::BasicResolver() : ArDefaultResolver() {
	std::cout << "Basic USD Resolver - Created Resolver\n\n";
}

BasicResolver::~BasicResolver() {
	std::cout << "Basic USD Resolver - Destroyed Resolver\n\n";
}

std::string BasicResolver::Resolve(const std::string& path) {
	return BasicResolver::ResolveWithAssetInfo(path, /* assetInfo = */ nullptr);
}

std::string
BasicResolver::ResolveWithAssetInfo(const std::string& path, ArAssetInfo* assetInfo) {


    std::string basicArPrefix = "uri:/";


	if (path.rfind(basicArPrefix, 0) == 0) { // if the path doesn't follow our basic:/ schema then interpret it using default AR

        std::string clean_path = path.substr(basicArPrefix.length()); // remove our uri:/ prefix

        std::string job_dir = std::getenv("JOB_DIR");

		std::string result = job_dir + "/" + clean_path; // absolute path by taking JOB_DIR env variable and adding the rest

		result.erase(std::remove_if(result.begin(), result.end(), ::isspace), result.end()); // strip any whitespace from result

        std::cout << "\n" << "Resolved URI: " << path << " to " << result << "\n";

		return result; // return aboslute path

	}

	else {
		return ArDefaultResolver::ResolveWithAssetInfo(path, assetInfo);
	}
}

void BasicResolver::UpdateAssetInfo(
	const std::string& identifier,
	const std::string& filePath,
	const std::string& fileVersion,
	ArAssetInfo* resolveInfo) {
	ArDefaultResolver::UpdateAssetInfo(identifier, filePath, fileVersion, resolveInfo);
}

VtValue BasicResolver::GetModificationTimestamp(
	const std::string& path,
	const std::string& resolvedPath) {
	return ArDefaultResolver::GetModificationTimestamp(path, resolvedPath);
}

bool BasicResolver::FetchToLocalResolvedPath(
	const std::string& path,
	const std::string& resolvedPath) {
	return true;

}

std::string BasicResolver::GetExtension(const std::string& path) {
    if (path.rfind("uri:/", 0) == 0) {
        return "usd";
    }
    else{
        return ArDefaultResolver::GetExtension(path);
    }

}

PXR_NAMESPACE_CLOSE_SCOPE