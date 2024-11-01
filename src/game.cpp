#include "game.hpp"
#include "shader.hpp"
#include "constants.hpp"
#include <iostream>

InfoScreenText::InfoScreenText(std::string title, std::string subtitle, float title_x, float title_y, float subtitle_x, float subtitle_y) : title(title), subtitle(subtitle), title_x(title_x), title_y(title_y), subtitle_x(subtitle_x), subtitle_y(subtitle_y) {}

void Game::processInput()
{
    if (glfwGetKey(this->window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        this->snake.on_direction_change(GLFW_KEY_LEFT);
    }
    if (glfwGetKey(this->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        this->snake.on_direction_change(GLFW_KEY_RIGHT);
    }
    if (glfwGetKey(this->window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        this->snake.on_direction_change(GLFW_KEY_UP);
    }
    if (glfwGetKey(this->window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        this->snake.on_direction_change(GLFW_KEY_DOWN);
    }

    if (glfwGetKey(this->window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        if (this->snake.get_is_game_over())
        {
            // The SPACE is treated as "reset" button
            this->snake.reset();
            this->info_screen->hide();
        }
        else
        {
            // The SPACE is treated as "play" button
            this->snake.play();
            this->info_screen->hide();
        }
    }

    if (glfwGetKey(this->window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        if (this->snake.get_is_playing())
        {
            this->snake.set_is_playing(false);
            this->info_screen->set_game_paused();
        }
        else
        {
            this->snake.set_is_playing(true);
            this->info_screen->hide();
        }
    }

    if (this->snake.get_is_game_over())
    {
        this->info_screen->set_game_over();
    }
}

void Game::render()
{
    // Clear the screen with a black color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Use the shader program
    this->shader.use();

    main_layout.draw(this->shader.get_shader_program(), VAO);

    this->processInput();
    snake.draw(this->shader.get_shader_program(), this->VAO);

    if (this->info_screen != nullptr)
    {
        this->info_screen->draw();
    }
}

Game::Game(GLFWwindow *window) : window(window), main_layout(Dimensions::grid_axis_count, Dimensions::grid_axis_count), snake(window, Dimensions::total_width / Dimensions::grid_axis_count), shader("src/shaders/vertex_shader.glsl", "src/shaders/fragment_shader.glsl"), info_screen(nullptr)
{
    // Define square vertices (two triangles to form a square)
    float vertices[] = {
        // first rectangle coordinates
        -0.5f, -1.0f, // bottom left
        0.5f, -1.0f,  // bottom right
        0.5f, 0.5f,   // top right
        -0.5f, 0.5f,  // top left
    };

    unsigned int indices[] = {
        // First square
        0, 1, 2, // First triangle
        2, 3, 0, // Second triangle
    };

    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Create VAO, VBO, and EBO
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glGenBuffers(1, &this->EBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind and set VBO data
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Bind and set EBO data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Set vertex attribute pointers
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Unbind the VBO and VAO (optional)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    this->info_screen = new InfoScreen(this->VAO, this->shader.get_shader_program());
}

Game::~Game()
{
    std::cout << "Destroying Buffers (VAO, VBO, EBO)..." << std::endl;
    glDeleteVertexArrays(1, &this->VAO);
    glDeleteBuffers(1, &this->VBO);
    glDeleteBuffers(1, &this->EBO);

    delete this->info_screen;
}

InfoScreen::InfoScreen(GLuint VAO, GLuint main_shader_program) : VAO(VAO), main_shader_program(main_shader_program), overlay(nullptr), hidden(false), text_type(InfoScreenTextType::Welcome)
{
    overlay = new Rectangle(glm::vec2(0.0f, 0.0f), glm::vec2(Dimensions::total_width, Dimensions::total_height), Colors::black_transparent);

    const float title_y = static_cast<float>(Dimensions::screen_height / 2) + 120.0f;
    const float subtitle_y = title_y - 50.0f;

    this->texts = {
        {InfoScreenTextType::Welcome, InfoScreenText(
                                          "SNAKE GAME IN C++",
                                          "Press enter to start the game",
                                          static_cast<float>(Dimensions::screen_width / 2) - 250.0f,
                                          title_y,
                                          static_cast<float>(Dimensions::screen_width / 2) - 180.0f,
                                          subtitle_y)},
        {InfoScreenTextType::GameOver, InfoScreenText(
                                           "GAME OVER",
                                           "Press enter to restart the game",
                                           static_cast<float>(Dimensions::screen_width / 2) - 155.0f,
                                           title_y,
                                           static_cast<float>(Dimensions::screen_width / 2) - 175.0f,
                                           subtitle_y)},
        {InfoScreenTextType::Paused, InfoScreenText(
                                         "PAUSED",
                                         "Press space to resume the game",
                                         static_cast<float>(Dimensions::screen_width / 2) - 102.5f,
                                         title_y,
                                         static_cast<float>(Dimensions::screen_width / 2) - 190.0f,
                                         subtitle_y)}};
}

InfoScreen::~InfoScreen()
{
    delete this->overlay;
}

void InfoScreen::draw()
{
    if (hidden)
        return;

    if (this->overlay != nullptr)
    {
        this->overlay->draw(this->main_shader_program, this->VAO);
    }

    this->text_context.use();

    // Render text
    this->text_context.render(
        this->texts[this->text_type].title,
        this->texts[this->text_type].title_x,
        this->texts[this->text_type].title_y,
        1.0f,
        Colors::white);
    this->text_context.render(
        this->texts[this->text_type].subtitle,
        this->texts[this->text_type].subtitle_x,
        this->texts[this->text_type].subtitle_y,
        0.5f,
        Colors::white);
}

void InfoScreen::hide()
{
    this->hidden = true;
}

void InfoScreen::set_game_over()
{
    this->text_type = InfoScreenTextType::GameOver;

    this->hidden = false;
}

void InfoScreen::set_game_paused()
{
    this->text_type = InfoScreenTextType::Paused;

    this->hidden = false;
}