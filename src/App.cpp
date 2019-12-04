/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** App.cpp
*/

#include <iostream>

#include "App.hpp"

App::App()
        : _sfWin{sf::VideoMode{WIN_W, WIN_H}, "Quadtree Demo", sf::Style::Close}
{
//    _sfWin.setFramerateLimit(145);

    _font.loadFromFile("Assets/Fonts/Cascadia.ttf");

    _fpsCounter.setFont(_font);
    _fpsCounter.setFillColor(sf::Color::Yellow);
    _fpsCounter.setPosition(10, 10);
    _fpsCounter.setCharacterSize(21);

    _entCount.setFont(_font);
    _entCount.setFillColor(sf::Color::Yellow);
    _entCount.setPosition(10, 42);
    _entCount.setCharacterSize(21);

    _frameManager.onSecond([&] {
        _fpsCounter.setString(std::to_string(_frameManager.getFramerate()) + " fps");
        _entCount.setString(std::to_string(_particles.size()) + " entities");
    });
}

void App::run()
{
    while (_sfWin.isOpen()) {
        _pollEvents();
        _tick();
        _render();

        _frameManager.update();
    }
}

void App::_pollEvents()
{
    while (_sfWin.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _sfWin.close();
        if (_event.type == sf::Event::EventType::MouseButtonPressed)
            for (int i = 0; i < 10; ++i)
                _particles.emplace_back(sf::Mouse::getPosition(_sfWin));
        if (_event.type == sf::Event::KeyPressed && _event.key.code == sf::Keyboard::Space)
            _particles.clear();
    }
}

void App::_tick()
{
    for (auto &particle : _particles)
        particle.tick(static_cast<float>(_frameManager.getDeltaTime()));
}

void App::_render()
{
    _sfWin.clear();

    for (const auto &particle : _particles)
        _sfWin.draw(particle.getShape());

    _sfWin.draw(_fpsCounter);
    _sfWin.draw(_entCount);

    _sfWin.display();
}
