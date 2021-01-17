package com.zoovu.puzzle

import org.springframework.boot.autoconfigure.SpringBootApplication
import org.springframework.boot.runApplication
import org.springframework.web.bind.annotation.RequestMapping
import org.springframework.web.bind.annotation.RequestMethod


@SpringBootApplication
class PuzzleApplication

fun main(args: Array<String>) {
	runApplication<PuzzleApplication>(*args)
}
