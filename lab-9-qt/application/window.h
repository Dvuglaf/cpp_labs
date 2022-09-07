#pragma once
#include <QMainWindow>
#include "Snake.h"
#include <QSize>
#include <QLabel>

/**
 * Основное окно игры.
 */
class MainWindow :public QMainWindow {

	Q_OBJECT
private:

	Snake* _snake; /**< Змейка. */
	Settings _settings; /**< Настройки. */
	QLabel* _statusBar; /**< Статус бар, показывающий текущий счет. */

private slots:
	/**
	 * Обработчик, отвечающий за обновление данных на статус баре.
	 */
	void refreshStatusBar();
	
	/**
	 * Обработчик, отвечающий за показ окна настроек.
	 */
	void showSettings();

public:
	/**
	 * Конструктор по умолчанию, задающий размер окна 576x576.
	 */
	MainWindow();

	/**
	 * Запрещенный конструктор копирования.
	 */
	MainWindow(const MainWindow&) = delete;

	/**
	 * Запрещенный оператор присваивания копированием.
	 */
	MainWindow& operator= (const MainWindow&) = delete;


};