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

    _statsText.setFont(_font);
    _statsText.setFillColor(sf::Color::Yellow);
    _statsText.setPosition(10, 10);
    _statsText.setCharacterSize(21);

    _frameManager.onSecond([&] {
        _statsText.setString(std::to_string(_frameManager.getFramerate()) + " fps\n" +
                             std::to_string(_particles.size()) + " entities");
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

void App::_keyPressed(sf::Keyboard::Key code)
{
    switch (code) {

        case sf::Keyboard::Space:
            _particles.clear();
            break;

        case sf::Keyboard::Q:
        case sf::Keyboard::Delete:
        case sf::Keyboard::Escape:
            _sfWin.close();
            break;

        case sf::Keyboard::F:
            _freeze = !_freeze;

        default:
            break;
    }
}

void App::_pollEvents()
{
    while (_sfWin.pollEvent(_event)) {
        if (_event.type == sf::Event::Closed)
            _sfWin.close();

        if (_event.type == sf::Event::KeyPressed)
            _keyPressed(_event.key.code);

        if (_event.type == sf::Event::EventType::MouseButtonPressed)
            for (int i = 0; i < 10; ++i)
                _particles.emplace_back(sf::Mouse::getPosition(_sfWin));
    }
}

void App::_tick()
{
    if (_freeze)
        return;

    // TODO: Update quads instead of recreating it

    _quadtree = Quadtree{0, 0, WIN_W, WIN_H};

    for (auto &particle : _particles) {
        _quadtree.insert(&particle);
        particle.tick(static_cast<float>(_frameManager.getDeltaTime()));
    }
}

void App::_render()
{
    _sfWin.clear();

    for (const auto &particle : _particles)
        _sfWin.draw(particle.getShape());

    _quadtree.draw(_sfWin);
    _sfWin.draw(_statsText);

    _sfWin.display();
}
