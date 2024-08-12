#ifndef SIMPLEENTITY_H
#define SIMPLEENTITY_H

#include <optional>

#include <QString>

class SimpleEntity final {
public:
    struct Tbl {
        static const QString TblName;

    public:
        static const QString Id;
        static const QString ParentId;
        static const QString Name;
    };

public:
    SimpleEntity() = default;
    explicit SimpleEntity(const int id);
    explicit SimpleEntity(const QString& name);
    SimpleEntity(const int id, const QString& name);

public:
    std::optional<int> getId() const;
    void setId(const std::optional<int>& id);

    std::optional<int> getParentId() const;
    void setParentId(const std::optional<int>& parentId);

    const QString getName() const;
    void setName(const QString &name);

private:
    // adjacency list!
    std::optional<int> m_id;
    std::optional<int> m_parentId;

    QString m_name;
};

#endif // SIMPLEENTITY_H
