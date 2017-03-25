// Copyright 2017-2017 the openage authors. See copying.md for legal info.

#pragma once

#include <functional>

#include "resource.h"


namespace openage {

class Player;
class Team;

/**
 * The categories of sub-scores that sum to a player's score.
 */
enum class score_category {
	/** 20% of units killed cost */
	military,
	/** 20% of alive units cost and 10% of resources */
	economy,
	/** 20% of researched technologies and 10 for each 1% of map explored*/
	technology,
	/** 20% of Castles and Wonders cost */
	society,
	SCORE_CATEGORY_COUNT
};

/**
 * Keeps track of a score and all the sub-scores
 */
class Score {
public:

	Score();

	void add_score(const score_category cat, double value);
	void add_score(const score_category cat, int value);

	void remove_score(const score_category cat, double value);
	void remove_score(const score_category cat, int value);

	void update_map_explored(double progress);

	void update_resources(const ResourceBundle & resources);

	/**
	 * Calculates the total score from the sub-scores.
	 * TODO update gui here
	 */
	virtual void update_score();

	// Getters

	int getScore(const score_category cat) const { return score[(int) cat]; }
	int getScore(const int index) const { return score[index]; }

	int getScoreTotal() const { return score_total; }

protected:

	int score[(int) score_category::SCORE_CATEGORY_COUNT];

	int score_exploration;
	int score_resources;

	// generated values

	int score_total;

private:

};


/**
 * The score of a player
 */
class ScorePlayer : public Score {
public:

	ScorePlayer(Player *player);

	virtual void update_score() override;

protected:

private:

	Player *player;
};


/**
 * The score of a team
 */
class ScoreTeam : public Score {
public:

	ScoreTeam(Team *team);

	virtual void update_score() override;

protected:

private:

	Team *team;
};

} // namespace openage

namespace std {

std::string to_string(const openage::score_category &cat);

/**
 * hasher for score_category
 * TODO decide if needed, not used at the moment
 */
template<> struct hash<openage::score_category> {
	typedef underlying_type<openage::score_category>::type underlying_type;
	typedef hash<underlying_type>::result_type result_type;
	result_type operator()( const openage::score_category& arg ) const {
		hash<underlying_type> hasher;
		return hasher(static_cast<underlying_type>(arg));
	}
};

} // namespace std
