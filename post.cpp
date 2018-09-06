#include "post.h"

using namespace Plurq;

bool Post::secret() const
{
    return !((*this)[QLatin1String("limited_to")].isNull());
}
