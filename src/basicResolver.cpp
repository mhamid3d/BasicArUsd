#include <string>
#include "pxr/pxr.h"
#include "pxr/usd/ar/defineResolver.h"
#include "basicResolver.h"


PXR_NAMESPACE_OPEN_SCOPE


AR_DEFINE_RESOLVER(BasicResolver, ArResolver);

BasicResolver::BasicResolver() : ArDefaultResolver() {}

BasicResolver::~BasicResolver() = default;

ArResolvedPath BasicResolver::_Resolve(const std::string& assetPath) const {

    std::string result = "";

    // DO STUFF WITH assetPath here and put the final result into "result"
	result = assetPath;

    return ArResolvedPath(result);
}

std::string BasicResolver::_GetExtension(const std::string& assetPath) const {
    return "usd";
}

std::string BasicResolver::_CreateIdentifier(const std::string& assetPath, const ArResolvedPath& anchorAssetPath) const {
    return assetPath;
}

PXR_NAMESPACE_CLOSE_SCOPE