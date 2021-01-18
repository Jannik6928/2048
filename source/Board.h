#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

using namespace std;

enum class Direction {
	Up,
	Down, 
	Left,
	Right
};

class Board
{
private:
	int _x_dim = 0;
	int _y_dim = 0;

	double _x = 0;
	double _y = 0;
	double _edge_length = 0;

	int** _board = nullptr;

	map<int, sf::Color> _colors;
	sf::Color _default;

	sf::Font _font;

	int _score = 0;

public:
	Board(int x, int y) {
		_x_dim = x;
		_y_dim = y;

		resize(x, y);
		fill(0);
	}
	Board(Board const& board) {
		_x_dim = board._x_dim;
		_y_dim = board._y_dim;

		_x = board._x;
		_y = board._y;
		_edge_length = board._edge_length;

		resize(_x, _y);
		for (int i = 0; i < _x_dim; i++) {
			for (int j = 0; j < _y_dim; j++) {
				_board[i][j] = board._board[i][j];
			}
		}

		_colors = board._colors;
		_default = board._default;

		_font = board._font;

		_score = board._score;
	}

	void resize(int x, int y) {
		
		_board = new int* [x];
		for (int i = 0; i < x; i++) {
			_board[i] = new int[y];
		}

	}
	void fill(int val) {
		for (int i = 0; i < _x_dim; i++) {
			for (int j = 0; j < _y_dim; j++) {
				_board[i][j] = val;
			}
		}
	}

	void set_position(double x, double y) {
		_x = x, _y = y;
	}
	void set_colors(sf::Color d, map<int, sf::Color> colors) {
		_default = d;
		_colors = colors;
	}
	void set_edge_length(double len) {
		_edge_length = len;
	}
	void set_font(sf::Font font) {
		_font = font;
	};

	int get(int x, int y) {
		return _board[x][y];
	}
	int** board() {
		return _board;
	}
	int score() {
		return _score;
	}

	bool move(int x, int y, Direction dir) {
		int dx = 0, dy = 0;

		if (dir == Direction::Up) {
			dx = 0;
			dy = -1;
		}
		if (dir == Direction::Down) {
			dx = 0;
			dy = 1;
		}
		if (dir == Direction::Left) {
			dx = -1;
			dy = 0;
		}
		if (dir == Direction::Right) {
			dx = 1;
			dy = 0;
		}


	}
	void merge(Direction dir) {
		if (dir == Direction::Down) {
			for (int i = 0; i < _x_dim; i++) {
				for (int j = _y_dim - 1; j > 0; j--) {
					if (_board[i][j] == _board[i][j - 1]) {
						_score += _board[i][j] * 2;
						_board[i][j] *= 2;
						_board[i][j - 1] = 0;
					}
				}
			}
		}
		if (dir == Direction::Up) {
			for (int i = 0; i < _x_dim; i++) {
				for (int j = 0; j < _y_dim - 1; j++) {
					if (_board[i][j] == _board[i][j + 1]) {
						_score += _board[i][j] * 2;
						_board[i][j] *= 2;
						_board[i][j + 1] = 0;
					}
				}
			}
		}
		if (dir == Direction::Right) {
			for (int i = 0; i < _y_dim; i++) {
				for (int j = _x_dim - 1; j > 0; j--) {
					if (_board[j - 1][i] == _board[j][i]) {
						_score += _board[j][i] * 2;
						_board[j][i] *= 2;
						_board[j - 1][i] = 0;
					}

				}

			}
		}
		if (dir == Direction::Left) {
			for (int i = 0; i < _y_dim; i++) {
				for (int j = 0; j < _x_dim - 1; j++) {
					if (_board[j][i] == _board[j + 1][i]) {
						_score += _board[j][i] * 2;
						_board[j][i] *= 2;
						_board[j + 1][i] = 0;
					}

				}
			}
		}
	}
	void move(Direction dir) {

		if (dir == Direction::Up) {
			for (int i = 0; i < _x_dim; i++) {
				int ct = 0;
				for (int j = 0; j < _y_dim; j++) {
					if (_board[i][j] == _board[i][j + 1]) {

					}
					if (_board[i][j] != 0) {
						_board[i][ct] = _board[i][j];
						ct++;
					}

				}
				while (ct < _y_dim) {
					_board[i][ct] = 0;
					ct++;
				}
			}
		}
		if (dir == Direction::Down) {
			for (int i = 0; i < _x_dim; i++) {
				int ct = 0;
				for (int j = _y_dim - 1; j >= 0; j--) {
					if (_board[i][j] != 0) {
						_board[i][_y_dim - 1 - ct] = _board[i][j];
						ct++;
					}

				}
				while (ct < _y_dim) {
					_board[i][_y_dim - 1 - ct] = 0;
					ct++;
				}
			}
		}
		if (dir == Direction::Left) {
			for (int i = 0; i < _y_dim; i++) {
				int ct = 0;
				for (int j = 0; j < _x_dim; j++) {
					if (_board[j][i] != 0) {
						_board[ct][i] = _board[j][i];
						ct++;
					}

				}
				while (ct < _x_dim) {
					_board[ct][i] = 0;
					ct++;
				}
			}
		}
		if (dir == Direction::Right) {
			for (int i = 0; i < _y_dim; i++) {
				int ct = 0;
				for (int j = _x_dim - 1; j >= 0; j--) {
					if (_board[j][i] != 0) {
						_board[_x_dim - 1 - ct][i] = _board[j][i];
						ct++;
					}

				}
				while (ct < _x_dim) {
					_board[_x_dim - 1 - ct][i] = 0;
					ct++;
				}
			}
		}
	}
	void add() {
		int ct = 0; 
		vector<pair<int, int>> open;
		for (int i = 0; i < _x_dim; i++) {
			for (int j = 0; j < _y_dim; j++) {
				if (_board[i][j] == 0) {
					open.push_back(pair<int, int>(i, j));
				}
			}
		}
		if (!open.size()) return;
		for (int i = 0; i < rand() % 2 + 1; i++) {
			pair<int, int> p = open[rand() % open.size()];
			if ((double)rand() / RAND_MAX < 0.25) _board[p.first][p.second] = 4;
			else _board[p.first][p.second] = 2;
		}
	}
	void update(Direction dir) {
		Board prev(*this);

		move(dir);
		merge(dir);
		move(dir);

		bool same = 1;
		for (int i = 0; i < _x_dim; i++) {
			for (int j = 0; j < _y_dim; j++) {
				if (_board[i][j] != prev._board[i][j]) {
					same = 0;
					break;
				}
			}
		}


		if (!same) add();
	}

	bool check_loss() {
		for (int i = 0; i < _x_dim; i++) {
			for (int j = 0; j < _y_dim; j++) {
				if (i + i < _x_dim) {
					if (_board[i][j] == _board[i + 1][j]) return 0;
				}
				if (j + 1 < _y_dim) {
					if (_board[i][j] == _board[i][j + 1]) return 0;
				}
				if (_board[i][j] == 0) return 0;
			}
		}
		return 1;
	}

	void reset() {
		for (int i = 0; i < _x_dim; i++) {
			for (int j = 0; j < _y_dim; j++) {
				_board[i][j] = 0;
			}
		}
		_score = 0;
	}

	vector<sf::Shape*> sprites() {
		vector<sf::Shape*> sp;

		for (int i = 0; i < _x_dim; i++) {
			for (int j = 0; j < _y_dim; j++) {
				sf::RectangleShape* sq = new sf::RectangleShape(sf::Vector2f(_edge_length, _edge_length));
				sq->setPosition(_edge_length * i + _x, _edge_length * j + _y);

				if (_colors.count(_board[i][j]) != 0) {
					sq->setFillColor(_colors[_board[i][j]]);
				}
				else {
					sq->setFillColor(_default);
				}
				sq->setOutlineThickness(5);
				sq->setOutlineColor(sf::Color(128,128,128));

				sp.push_back(sq);
			}
		}

		return sp;
	}
	vector<sf::Text*> text() {
		vector<sf::Text*> tx;

		for (int i = 0; i < _x_dim; i++) {
			for (int j = 0; j < _y_dim; j++) {
				sf::Text* t = new sf::Text;
				t->setFillColor(sf::Color::Black);
				t->setFont(_font);
				if (_board[i][j] != 0) t->setString(to_string(_board[i][j]));
				t->setPosition(_edge_length * i + _x, _edge_length * j + _y);

				t->setCharacterSize(_edge_length / 3);

				tx.push_back(t);
			}
		}

		return tx;
	}
};

