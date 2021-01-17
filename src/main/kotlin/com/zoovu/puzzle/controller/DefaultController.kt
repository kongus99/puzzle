package com.zoovu.puzzle.controller

import org.springframework.stereotype.Controller
import org.springframework.web.bind.annotation.GetMapping
import org.springframework.web.bind.annotation.RequestMapping
import org.springframework.web.bind.annotation.RequestMethod

@Controller("defaultController")
class LoginController {

    @GetMapping(value = ["/"])
    fun index(): String {
        return "indexProduction.html"
    }
}
