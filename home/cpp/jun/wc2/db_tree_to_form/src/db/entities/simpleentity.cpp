#include "db/entities/simpleentity.h"

const QString SimpleEntity::Tbl::TblName = QString("SimpleEntity");

const QString SimpleEntity::Tbl::Id = QString("Id");
const QString SimpleEntity::Tbl::ParentId = QString("ParentId");
const QString SimpleEntity::Tbl::Name = QString("Name");

SimpleEntity::SimpleEntity(const int id): m_id(id) {}
SimpleEntity::SimpleEntity(const QString& name): m_name(name) {}
SimpleEntity::SimpleEntity(const int id, const QString& name)
    : m_id(id), m_name(name) {}

std::optional<int> SimpleEntity::getId() const {
    return m_id;
}

void SimpleEntity::setId(const std::optional<int> &id) {
    m_id = id;
}

const QString SimpleEntity::getName() const {
    return m_name;
}

void SimpleEntity::setName(const QString &name) {
    m_name = name;
}

std::optional<int> SimpleEntity::getParentId() const {
    return m_parentId;
}

void SimpleEntity::setParentId(const std::optional<int>& parentId) {
    m_parentId = parentId;
}
