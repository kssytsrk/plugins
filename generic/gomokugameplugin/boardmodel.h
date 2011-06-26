/*
 * boardmodel.h - Gomoku Game plugin
 * Copyright (C) 2011  Aleksey Andreev
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * You can also redistribute and/or modify this program under the
 * terms of the Psi License, specified in the accompanied COPYING
 * file, as published by the Psi Project; either dated January 1st,
 * 2005, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#ifndef BOARDMODEL_H
#define BOARDMODEL_H

#include <QAbstractTableModel>
#include <QStringList>

#include "gameelement.h"

class BoardModel : public QAbstractTableModel
{
Q_OBJECT
public:
	enum GameStatus {
		StatusNone,
		StatusWaitingOpponent,
		StatusWaitingAccept,
		StatusThinking,
		StatusEndGame,
		StatusError,
		StatusWin,
		StatusLose,
		StatusDraw
	};
	explicit BoardModel(QObject *parent = 0);
	~BoardModel();
	void init(GameElement::ElementType myElement);
	virtual Qt::ItemFlags flags(const QModelIndex & index) const;
	virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	virtual bool setData(const QModelIndex &index, const QVariant &value, int role);
	virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;
	virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;
	// --
	GameElement *getGameElement(int x, int y);
	bool clickToBoard(QModelIndex index);
	bool opponentTurn(int x, int y);
	void setAccept();
	void setError();
	void setClose();
	void setWin();
	void opponentDraw();
	void setResign();
	int  turnNum();
	GameElement::ElementType elementType();
	bool doSwitchColor(bool local_init);
	QString saveToString() const;
	bool loadFromString(const QString settings, bool my_load);
	void setSelect(int x, int y);
	//--
	int selectX;
	int selectY;

private:
	GameStatus gameStatus;
	GameElement::ElementType myElement_;
	int boardSizeX;
	int boardSizeY;
	int columnCount_;
	int rowCount_;
	QList<GameElement*> gameElements;
	int lastX;
	int lastY;
	int turnsCount;
	int blackCount;
	int whiteCount;
	bool loadGameFlag;

private:
	void reset();
	void setHeaders();
	void setGameStatus(GameStatus status);
	bool setElementToBoard(int x, int y, bool my_element);
	int  getGameElementIndex(int x, int y) const;
	bool setGameElement(GameElement* el);
	bool checkGameForLose();
	bool checkGameForDraw();

private slots:
	void setLose();
	void setMyDraw();

signals:
	void changeGameStatus(BoardModel::GameStatus);
	void setupElement(int x, int y);
	void lose();
	void draw();
	void switchColor();
	void doPopup(const QString);
	void playSound(const QString);

};

#endif // BOARDMODEL_H
