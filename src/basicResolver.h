#include "pxr/pxr.h"
#include "pxr/usd/ar/api.h"
#include "pxr/usd/ar/resolver.h"
#include "pxr/usd/ar/defaultResolver.h"
#include "pxr/usd/ar/resolvedPath.h"
#include <string>

PXR_NAMESPACE_OPEN_SCOPE


class BasicResolver final
	: public ArDefaultResolver
{
public:
	BasicResolver();
	virtual ~BasicResolver();
protected:
	AR_API
		ArResolvedPath _Resolve(const std::string& assetPath) const final;
	AR_API
		std::string _GetExtension(const std::string& assetPath) const final;
	AR_API
	    std::string _CreateIdentifier(const std::string& assetPath, const ArResolvedPath& anchorAssetPath) const final;
};

PXR_NAMESPACE_CLOSE_SCOPE