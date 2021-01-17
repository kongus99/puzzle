package com.zoovu.puzzle.controller

import org.springframework.web.bind.annotation.*
import java.time.Duration
import java.time.Instant
import java.time.LocalDateTime
import java.time.ZoneId
import java.time.temporal.ChronoUnit

@RestController
class LeaderBoardController {

    val persistedScores = mutableMapOf<String, PersistedScore>(
        "Adam" to Score("Adam", 100).persist(),
        "Eve" to Score("Eve", 200).persist(),
        "Cain" to Score("Cain", 300).persist(),
        "Abel" to Score("Abel", 400).persist(),
        "Seth" to Score("Seth", 500).persist(),
    )

    @GetMapping(value = ["/api/leaderboard"])
    fun leaderBoard(@RequestParam(required = false) period: ChronoUnit?): List<PersistedScore> {
        val currentDuration = duration()
        return persistedScores.values.toList()
            .filter { ps ->
                period?.let { p -> currentDuration(ps.timestamp).minus(p.duration).isNegative } ?: true
            }
            .sortedBy { ps -> ps.result }
            .take(20)
    }

    @PostMapping(value = ["/api/leaderboard"])
    fun saveScore(@RequestBody(required = true) score: Score): PersistedScore? {
        persistedScores[score.name] = score.persist()
        return persistedScores[score.name]
    }

    private fun duration(): (Long) -> Duration {
        val now = LocalDateTime.ofInstant(Instant.now(), ZoneId.systemDefault())
        return fun(millis: Long): Duration {
            return Duration.between(LocalDateTime.ofInstant(Instant.ofEpochMilli(millis), ZoneId.systemDefault()), now)
        }
    }
}

data class Score(val name: String, val result: Int) {
    fun persist(): PersistedScore {
        return PersistedScore(name, result, System.currentTimeMillis())
    }
}

data class PersistedScore(val name: String, val result: Int, val timestamp: Long)

