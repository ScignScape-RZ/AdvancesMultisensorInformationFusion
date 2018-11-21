
#include "rz-re-block-entry.h"

#include "rzns.h"


USING_RZNS(RECore)

RE_Block_Entry::RE_Block_Entry(int call_id)
 : Flags(0), call_id_(call_id), nested_depth_(0),
   lexical_scope_(nullptr)
{

}

