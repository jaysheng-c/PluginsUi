/**
  ********************************************************************************
  * @file           : main_tree_view.cpp
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/19
  * @version        : 1.0
  ********************************************************************************
  */

#include "main_tree_view.h"
#include <QAbstractItemModel>
#include <QTimer>


namespace {

constexpr char gStyle[] =
    "QTreeView {\n"
    "   background-color: #2B2D30;\n"
    "   border: none;\n"
    "   color: #FFFFFF;\n"
    "   outline: 0; /* Remove focus border */\n"
    "}\n\n"
    "QTreeView::item {\n"
    "   height: 15px;\n"
    "   padding: 2px;\n"
    "}\n\n"
    "QTreeView::item:selected:active {\n"
    "   color: #FFFFFF;\n"
    "   background-color: #2E436E;\n"
    "}\n\n"
    "QTreeView::item::selected:!active {\n"
    "   color: #FFFFFF;\n"
    "   background-color: #43454A;\n"
    "}";

class Node final : public QObject {
public:
    struct Data {
        int type;
        QString name;
        QList<std::shared_ptr<Node>> children;
        QPointer<Node> parent;
    };
    explicit Node(const QString &name, const int type, QObject *parent = nullptr)
        : QObject(parent), m_data{type, name, {}, parentNode()} {}
    explicit Node(QObject *parent = nullptr) : Node("root", -1, parent) {}
    ~Node() override
    {
        if (m_data.parent) {
            qDebug() << "parent: " + m_data.parent->data().name + ", child: " + m_data.name;
            return;
        }
        qDebug() << "delete node:" << m_data.name;
    }

    NODISCARD Data &data() { return m_data; }
    NODISCARD const Data &data() const { return m_data; }

    NODISCARD const QPointer<Node> &parentNode() const { return m_data.parent; }
    NODISCARD QPointer<Node> &parentNode() { return m_data.parent; }

    NODISCARD QList<std::shared_ptr<Node>> *children() { return &(m_data.children); }

    void addChild(const QString &name)
    {
        auto node = std::make_shared<Node>();
        node->data().name = name;
        node->data().type = m_data.type;
        node->parentNode() = this;
        m_data.children.append(std::move(node));
    }
private:
    Data m_data;
};

class FreeNodeChild {
public:
    void operator()(Node *root) const
    {
        if (root) {
            root->data().children.resize(0);
        }
    }
};

}


class MainTreeView::Model final : public QAbstractItemModel {
public:
    explicit Model(QObject *parent = nullptr)
        : QAbstractItemModel(parent), m_root(std::make_unique<Node>("root", -1)) {}
    ~Model() override { clearModel(); }

    NODISCARD QModelIndex parent(const QModelIndex &child) const override
    {
        if (!child.isValid()) {
            return {};
        }
        const auto *childNode = static_cast<Node*>(child.internalPointer());
        const auto parent = childNode->data().parent;
        if (parent == m_root.get()) {
            return {};
        }
        int row = 0;
        if (parent->data().parent) {
            // row = parent->parent->children.indexOf(parent);
            while (row < parent->data().parent->data().children.size()) {
                if (parent == parent->data().parent->data().children[row].get()) {
                    break;
                }
                ++row;
            }
            if (row >= parent->data().parent->data().children.size()) {
                return {};
            }
        }
        return createIndex(row, 0, parent);
    }
    NODISCARD QModelIndex index(const int row, const int column, const QModelIndex &parent) const override
    {
        if (hasIndex(row, column, parent)) {
            const auto *parentNode = nodeFromIndex(parent);
            if (row < parentNode->data().children.size()) {
                return createIndex(row, column, parentNode->data().children[row].get());
            }
        }
        return {};
    }
    NODISCARD int rowCount(const QModelIndex &parent) const override
    {
        if (parent.column() > 0) {
            return 0;
        }
        const auto *parentNode = nodeFromIndex(parent);
        return parentNode->data().children.size();
    }
    NODISCARD int columnCount(const QModelIndex &parent) const override
    {
        Q_UNUSED(parent)
        return 1;
    }
    NODISCARD QVariant data(const QModelIndex &index, const int role) const override
    {
        if (!index.isValid()) {
            return {};
        }
        if (auto *node = static_cast<Node*>(index.internalPointer())) {
            if (role == Qt::DisplayRole) {
                return node->data().name;
            }
        }
        return {};
    }
    NODISCARD Node *getNode(const int type, const QString &name) const
    {
        auto *children = m_root->children();
        const auto it = std::find_if(children->begin(), children->end(), [type](const std::shared_ptr<Node> &child) {
            return child->data().type == type;
        });
        if (it != children->end()) {
            return it->get();
        }
        m_root->children()->append(std::make_shared<Node>(name, type));
        m_root->children()->last()->data().parent = m_root.get();
        return m_root->children()->last().get();
    }
    NODISCARD QVariant headerData(const int section, const Qt::Orientation orientation, const int role) const override
    {
        if (orientation == Qt::Horizontal || role == Qt::DisplayRole) {
            return "节点名称";
        }
        return QAbstractItemModel::headerData(section, orientation, role);
    }

    // set & delete
    MAYBE_UNUSED bool setData(const QModelIndex &index, const QVariant &value, int role) override
    {
        if (index.isValid()) {
            if (auto *node = static_cast<Node*>(index.internalPointer())) {
                if (index.row() < node->data().children.size() && (role == Qt::DisplayRole || Qt::EditRole)) {
                    node->data().children[index.row()]->data().name = value.toString();
                    emit dataChanged(index, index, {role});
                    return true;
                }
            }
        }
        return QAbstractItemModel::setData(index, value, role);
    }
    MAYBE_UNUSED bool insertRows(const int position, const int count, const QModelIndex &parent) override
    {
        auto *parentNode = nodeFromIndex(parent);
        if (parentNode == nullptr) {
            return false;
        }
        beginInsertRows(parent, position, position + count - 1);
        for (int i = 0; i < count; ++i) {
            auto newNode = std::make_shared<Node>();
            newNode->data().parent = parentNode;
            parentNode->data().children.insert(position + i, newNode);
        }
        endInsertRows();
        return true;
    }
    MAYBE_UNUSED bool removeRows(const int position, const int count, const QModelIndex &parent) override
    {
        auto *parentNode = nodeFromIndex(parent);
        if (parentNode == nullptr) {
            return false;
        }
        beginRemoveRows(parent, position, position + count - 1);
        for (int i = 0; i < count; ++i) {
            parentNode->data().children.removeAt(position);
        }
        endRemoveRows();
        return true;
    }
    MAYBE_UNUSED bool insertColumns(const int position, const int columns, const QModelIndex &parent) override
    {
        Q_UNUSED(position)
        Q_UNUSED(columns)
        Q_UNUSED(parent)
        qInfo() << "can not support insertColumns";
        return false;
    }
    MAYBE_UNUSED bool removeColumns(const int position, const int columns, const QModelIndex &parent) override
    {
        Q_UNUSED(position)
        Q_UNUSED(columns)
        Q_UNUSED(parent)
        qInfo() << "can not support removeColumns";
        return false;
    }

    void resetData(const QString &data)
    {
        beginResetModel();
        FreeNodeChild()(m_root.get());
        // m_parser->parser(data);
        endResetModel();
    }
    void clearModel()
    {
        beginResetModel();
        FreeNodeChild()(m_root.get());
        endResetModel();
    }
    void update()
    {
        beginResetModel();
        endResetModel();
    }

private:
    NODISCARD Node *nodeFromIndex(const QModelIndex &index) const
    {
        if (!index.isValid())
            return m_root.get();
        return static_cast<Node*>(index.internalPointer());
    }

    std::unique_ptr<Node> m_root;
};


MainTreeView::MainTreeView(QWidget *parent)
    : QTreeView(parent), m_model(new Model(this))
{
    this->setStyleSheet(gStyle);
}

void MainTreeView::initTree()
{
    this->setModel(m_model);
    // QTimer::singleShot(2 * 1000, [this]() {
    //     m_model->clearModel();
    // });

    // 初始化支持类型
    m_supportType = {
        {Project, "Project"},
        {Excel, "Excel"},
    };
}

bool MainTreeView::supportedType(const int type) const
{
    return m_supportType.contains(type);
}

MainTreeView::Result MainTreeView::addNode(const QString &name, const int type) const
{
    if (!supportedType(type)) {
        const QString msg =  "unsupported type: " + QString::number(type);
        qWarning() << msg;
        return {false, msg};
    }
    auto *parentNode = m_model->getNode(type, m_supportType.value(type));
    const auto *children = parentNode->children();
    const auto it = std::find_if(children->begin(), children->end(), [name](const std::shared_ptr<Node> &child) {
        return child->data().name == name;
    });
    if (it != children->end()) {
        const QString msg = "node already exists: " + name;
        qWarning() << msg;
        return {false, msg};
    }
    parentNode->addChild(name);
    m_model->update();
    return {true, ""};
}



