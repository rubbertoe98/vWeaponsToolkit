#ifndef RAPIDXML_EXT_H_
#define RAPIDXML_EXT_H_
#include "rapidxml.hpp"
/* Adding declarations to make it compatible with gcc 4.7 and greater */
namespace rapidxml {
namespace internal {
    template <class OutIt, class Ch>
    inline OutIt print_children(OutIt out, const xml_node<Ch>* node, int flags, int indent);

template <class OutIt, class Ch>
inline OutIt print_attributes(OutIt out, const xml_node<Ch>* node, int flags);

template <class OutIt, class Ch>
inline OutIt print_data_node(OutIt out, const xml_node<Ch>* node, int flags, int indent);

template <class OutIt, class Ch>
inline OutIt print_cdata_node(OutIt out, const xml_node<Ch>* node, int flags, int indent);

template <class OutIt, class Ch>
inline OutIt print_element_node(OutIt out, const xml_node<Ch>* node, int flags, int indent);

template <class OutIt, class Ch>
inline OutIt print_declaration_node(OutIt out, const xml_node<Ch>* node, int flags, int indent);

template <class OutIt, class Ch>
inline OutIt print_comment_node(OutIt out, const xml_node<Ch>* node, int flags, int indent);

template <class OutIt, class Ch>
inline OutIt print_doctype_node(OutIt out, const xml_node<Ch>* node, int flags, int indent);

template <class OutIt, class Ch>
inline OutIt print_pi_node(OutIt out, const xml_node<Ch>* node, int flags, int indent);
}
}
#include "rapidxml_print.hpp"

#endif /* RAPIDXML_EXT_H_ */
