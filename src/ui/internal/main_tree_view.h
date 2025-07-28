/**
  ********************************************************************************
  * @file           : main_tree_view.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/19
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef MAIN_TREE_VIEW_H
#define MAIN_TREE_VIEW_H

#include <QPointer>
#include <QTreeView>
#include "macro.h"

class MainTreeView final : public QTreeView {
Q_OBJECT
public:
    struct Result {
        const bool flag = false;
        const QString &msg;
    };
    enum Type {
        None = 0x000,
        Project = 0x001,
        Excel = 0x002,

        External = 0x100,
    };
    Q_ENUM(Type)

    explicit MainTreeView(QWidget *parent = nullptr);
    void initTree();
    NODISCARD bool supportedType(int type) const;
    NODISCARD Result addNode(const QString &name, int type) const;
private:
    class Model;
    Model *m_model;

    QHash<int, QString> m_supportType;
};



#endif //MAIN_TREE_VIEW_H
