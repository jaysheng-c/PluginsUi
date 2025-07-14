/**
  ********************************************************************************
  * @file           : table_view.h
  * @author         : jaysheng
  * @brief          : None
  * @attention      : None
  * @date           : 2025/07/14
  * @version        : 1.0
  ********************************************************************************
  */

#ifndef TABLE_VIEW_H
#define TABLE_VIEW_H

#include <QTableView>

class TableModel;

class TableView final : public QTableView {
Q_OBJECT
public:
    explicit TableView(QWidget *parent = nullptr);
    void initTable();
protected:
    void keyPressEvent(QKeyEvent *event) override;
private:
    TableModel *m_model;
};



#endif //TABLE_VIEW_H
