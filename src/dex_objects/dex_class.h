#ifndef __DEX_CLASS_H__
# define __DEX_CLASS_H__

# include <stdint.h>

/*
appears in the class_defs section
alignment: 4 bytes
*/

struct s_class_def_item
{
    // index into the type_ids list for this class. This must be a class 
    // type, and not an array or primitive type.
    uint32_t class_idx;

    // access flags for the class (public, final, etc.). See "access_flags
    //  Definitions" for details. 
    uint32_t access_flags;

    // index into the type_ids list for the superclass, or the constant
    // value NO_INDEX if this class has no superclass (i.e., it is a
    // root class such as Object). If present, this must be a class type,
    // and not an array or primitive type. 
    uint32_t superclass_idx;

    // offset from the start of the file to the list of interfaces,
    // or 0 if there are none. This offset should be in the data 
    // section, and the data there should be in the format specified
    // by "type_list" below. Each of the elements of the list must be
    // a class type (not an array or primitive type), and there must 
    // not be any duplicates. 
    uint32_t interfaces_off;

    // index into the string_ids list for the name of the file containing
    // the original source for (at least most of) this class, or the special
    // value NO_INDEX to represent a lack of this information. The
    // debug_info_item of any given method may override this source file, 
    // but the expectation is that most classes will only come from one source
    // file.
    uint32_t source_file_idx;

    // offset from the start of the file to the annotations structure for
    // this class, or 0 if there are no annotations on this class. This offset,
    // if non-zero, should be in the data section, and the data there should
    // be in the format specified by "annotations_directory_item" below, with
    // all items referring to this class as the definer. 
    uint32_t annotations_off;

    // offset from the start of the file to the associated class data for this
    // item, or 0 if there is no class data for this class. (This may be the
    // case, for example, if this class is a marker interface.) The offset, if
    // non-zero, should be in the data section, and the data there should be in
    // the format specified by "class_data_item" below, with all items
    // referring to this class as the definer. 
    uint32_t class_data_off;

    // offset from the start of the file to the list of initial values for
    // static fields, or 0 if there are none (and all static fields are to
    // be initialized with 0 or null). This offset should be in the data
    // section, and the data there should be in the format specified by
    // "encoded_array_item" below. The size of the array must be no larger
    // than the number of static fields declared by this class, and the
    // elements correspond to the static fields in the same order as declared
    // in the corresponding field_list. The type of each array element must
    // match the declared type of its corresponding field. If there are fewer
    // elements in the array than there are static fields, then the leftover
    // fields are initialized with a type-appropriate 0 or null. 
    uint32_t static_values_off;
};
typedef struct s_class_def_item class_def_item;

#endif/*!__DEX_CLASS_H__*/
