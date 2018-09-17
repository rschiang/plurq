#include "post.h"

using namespace Plurq;

bool Post::secret() const
{
    return !((*this)[QLatin1String("limited_to")].isNull());
}

QString Post::translatedQualifier() const
{
    // Return translated qualifier if applicable
    return (*this)[QLatin1String("qualifier_translated")].toString(qualifier());
}
