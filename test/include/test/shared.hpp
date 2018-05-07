#include <catch/catch.hpp>
#include <fakeit.hpp>

#include <core/core.hpp>
/* template hack to allow acess to private members see:             *
 * https://gist.github.com/mdadams/98710ba3478f306633df20dca47d5cd9 */

#define PRIVATE_TAG()                                                                                                  \
    template <typename Tag> typename Tag::type saved_private_v;                                                        \
    template <typename Tag, typename Tag::type x> bool save_private_v = (saved_private_v<Tag> = x);

#define COMMA ,
/* creates tag class for acessing private buttons varible */

#define TAG_SV(classname, varible_name, varible_type)                                                                  \
    struct classname##_##varible_name {                                                                                \
        using type = varible_type*;                                                                                    \
    };                                                                                                                 \
    template bool save_private_v<classname##_##varible_name, &classname::varible_name>;

#define TAG_SCV(classname, varible_name, varible_type)                                                                 \
    struct classname##_##varible_name {                                                                                \
        using type = varible_type* const;                                                                              \
    };                                                                                                                 \
    template bool save_private_v<classname##_##varible_name, &classname::varible_name>;

#define TAG_V(classname, varible_name, varible_type)                                                                   \
    struct classname##_##varible_name {                                                                                \
        using type = varible_type classname::*;                                                                        \
    };                                                                                                                 \
    template bool save_private_v<classname##_##varible_name, &classname::varible_name>;

#define TAG_CV(classname, varible_name, varible_type)                                                                  \
    struct classname##_##varible_name {                                                                                \
        using type = varible_type classname::*const;                                                                   \
    };                                                                                                                 \
    template bool save_private_v<classname##_##varible_name, &classname::varible_name>;
