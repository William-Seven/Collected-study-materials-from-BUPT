#include "ast.h"

ArrayTypeNode::ArrayTypeNode(ArrayTypeNode* other) {
    this->node_type = NODE_ARRAY_TYPE;
    this->type = other->type;
    vector<ASTNode*> periodList = dynamic_cast<PeriodListNode*>(other->period_list)->period_list;
    vector<ASTNode*> thisPeriodList;
    for (const auto& it : periodList) {
        PeriodNode* period = dynamic_cast<PeriodNode*>(it);
        thisPeriodList.push_back(new PeriodNode(period->start, period->end));
    }
    this->period_list = new PeriodListNode(thisPeriodList);
}
BasicTypeNode::BasicTypeNode(BasicTypeNode* other) {
    this->node_type = NODE_BASIC_TYPE;
    this->type = other->type;
}
FieldNode::FieldNode(FieldNode* oth) {
    node_type = NODE_FIELD;

    vector<string> idList = dynamic_cast<IdentifierListNode*>(oth->id_list)->identifier_list;
    this->id_list = new IdentifierListNode(idList);

    auto othType = (oth->type)->node_type;
    if (othType == NODE_BASIC_TYPE) {
        this->type = new BasicTypeNode(dynamic_cast<BasicTypeNode*>(oth->type));
    } else if (othType == NODE_ARRAY_TYPE) {
        this->type = new ArrayTypeNode(dynamic_cast<ArrayTypeNode*>(oth->type));
    } else if (othType == NODE_RECORD_TYPE) {
        RecordTypeNode* recTypeNode = dynamic_cast<RecordTypeNode*>(oth->type);
        vector<ASTNode*> fieldList = dynamic_cast<FieldListNode*>(recTypeNode->field_list)->field_list;
        vector<ASTNode*> thisFieldList;
        for (const auto& it : fieldList) {
            FieldNode* field = dynamic_cast<FieldNode*>(it);
            thisFieldList.push_back(new FieldNode(field));
        }
        this->type = new RecordTypeNode(new FieldListNode(thisFieldList), recTypeNode->name);
    }
}
FieldNode::FieldNode(ASTNode* oth, IdentifierListNode* othId) {
    node_type = NODE_FIELD;

    vector<string> idList = dynamic_cast<IdentifierListNode*>(othId)->identifier_list;
    this->id_list = new IdentifierListNode(idList);

    auto othType = oth->node_type;
    if (othType == NODE_BASIC_TYPE) {
        this->type = new BasicTypeNode(dynamic_cast<BasicTypeNode*>(oth));
    } else if (othType == NODE_ARRAY_TYPE) {
        this->type = new ArrayTypeNode(dynamic_cast<ArrayTypeNode*>(oth));
    } else if (othType == NODE_RECORD_TYPE) {
        RecordTypeNode* recTypeNode = dynamic_cast<RecordTypeNode*>(oth);
        vector<ASTNode*> fieldList = dynamic_cast<FieldListNode*>(recTypeNode->field_list)->field_list;
        vector<ASTNode*> thisFieldList;
        for (const auto& it : fieldList) {
            FieldNode* field = dynamic_cast<FieldNode*>(it);
            thisFieldList.push_back(new FieldNode(field));
        }
        this->type = new RecordTypeNode(new FieldListNode(thisFieldList), recTypeNode->name);
    }
}