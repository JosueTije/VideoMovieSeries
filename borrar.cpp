#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class Video
{
public:
    Video(int id, const std::string &nombre, double duracion, const std::string &genero)
        : id(id), nombre(nombre), duracion(duracion), genero(genero), sumaCalificaciones(0), numCalificaciones(0) {}

    virtual ~Video() = default;

    virtual void mostrar() const
    {
        std::cout << "ID: " << id << " - " << nombre << " (" << duracion << " mins, " << genero << ") - Calificación promedio: " << getCalificacionPromedio() << std::endl;
    }

    void agregarCalificacion(double calificacion)
    {
        sumaCalificaciones += calificacion;
        numCalificaciones++;
    }

    double getCalificacionPromedio() const
    {
        return (numCalificaciones > 0) ? (sumaCalificaciones / numCalificaciones) : 0;
    }

    int getId() const { return id; }
    const std::string &getNombre() const { return nombre; }
    const std::string &getGenero() const { return genero; }

protected:
    int id;
    std::string nombre;
    double duracion;
    std::string genero;
    double sumaCalificaciones;
    int numCalificaciones;
};

class Pelicula : public Video
{
public:
    Pelicula(int id, const std::string &nombre, double duracion, const std::string &genero)
        : Video(id, nombre, duracion, genero) {}
};

class Episodio
{
public:
    Episodio(const std::string &titulo, int temporada, double calificacion)
        : titulo(titulo), temporada(temporada), calificacion(calificacion) {}

    void mostrar() const
    {
        std::cout << "    " << titulo << " - Temporada " << temporada << " - Calificación: " << calificacion << std::endl;
    }

    double getCalificacion() const { return calificacion; }

private:
    std::string titulo;
    int temporada;
    double calificacion;
};

class Serie : public Video
{
public:
    Serie(int id, const std::string &nombre, double duracion, const std::string &genero)
        : Video(id, nombre, duracion, genero) {}

    void agregarEpisodio(const Episodio &episodio)
    {
        episodios.push_back(episodio);
        agregarCalificacion(episodio.getCalificacion());
    }

    void mostrarEpisodios() const
    {
        for (const auto &episodio : episodios)
        {
            episodio.mostrar();
        }
    }

    void mostrar() const override
    {
        Video::mostrar();
        mostrarEpisodios();
    }

private:
    std::vector<Episodio> episodios;
};

std::vector<Video *> videos;

void cargarArchivo()
{
    std::string nombreArchivo;
    std::cout << "Ingrese el nombre del archivo de datos: ";
    std::cin >> nombreArchivo;

    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open())
    {
        std::cout << "Archivo no encontrado." << std::endl;
        return;
    }

    videos.clear();
    std::string linea;
    while (getline(archivo, linea))
    {
        std::istringstream stream(linea);
        std::string tipo;
        int id;
        std::string nombre;
        double duracion;
        std::string genero;
        double calificacion;
        getline(stream, tipo, ',');
        stream >> id;
        stream.ignore();
        getline(stream, nombre, ',');
        stream >> duracion;
        stream.ignore();
        getline(stream, genero, ',');
        stream >> calificacion;

        if (tipo == "pelicula")
        {
            Pelicula *pelicula = new Pelicula(id, nombre, duracion, genero);
            pelicula->agregarCalificacion(calificacion);
            videos.push_back(pelicula);
        }
        else if (tipo == "serie")
        {
            Serie *serie = new Serie(id, nombre, duracion, genero);
            videos.push_back(serie);
        }
        else if (tipo == "episodio")
        {
            int serieId, temporada;
            std::string titulo;
            stream.ignore();
            stream >> serieId;
            stream.ignore();
            getline(stream, titulo, ',');
            stream >> temporada;
            stream.ignore();
            stream >> calificacion;

            Episodio episodio(titulo, temporada, calificacion);
            for (auto &video : videos)
            {
                Serie *serie = dynamic_cast<Serie *>(video);
                if (serie && serie->getId() == serieId)
                {
                    serie->agregarEpisodio(episodio);
                    break;
                }
            }
        }
    }
    archivo.close();
    std::cout << "Archivo cargado correctamente." << std::endl;
}

void mostrarVideos()
{
    for (const auto &video : videos)
    {
        video->mostrar();
    }
}

void mostrarEpisodiosDeSerie()
{
    int serieId;
    std::cout << "Ingrese el ID de la serie: ";
    std::cin >> serieId;

    for (const auto &video : videos)
    {
        Serie *serie = dynamic_cast<Serie *>(video);
        if (serie && serie->getId() == serieId)
        {
            serie->mostrar();
            return;
        }
    }
    std::cout << "Serie no encontrada." << std::endl;
}

void mostrarPeliculas()
{
    for (const auto &video : videos)
    {
        Pelicula *pelicula = dynamic_cast<Pelicula *>(video);
        if (pelicula)
        {
            pelicula->mostrar();
        }
    }
}

void calificarVideo()
{
    int videoId;
    double calificacion;
    std::cout << "Ingrese el ID del video a calificar: ";
    std::cin >> videoId;
    std::cout << "Ingrese la calificación otorgada: ";
    std::cin >> calificacion;

    for (auto &video : videos)
    {
        if (video->getId() == videoId)
        {
            video->agregarCalificacion(calificacion);
            std::cout << "Video calificado correctamente." << std::endl;
            return;
        }
    }
    std::cout << "Video no encontrado." << std::endl;
}

int main()
{
    int opcion;
    do
    {
        std::cout << "Menu:\n";
        std::cout << "1. Cargar archivo de datos\n";
        std::cout << "2. Mostrar los videos en general con sus calificaciones\n";
        std::cout << "3. Mostrar los episodios de una determinada serie con sus calificaciones\n";
        std::cout << "4. Mostrar las películas con sus calificaciones\n";
        std::cout << "5. Calificar un video\n";
        std::cout << "0. Salir\n";
        std::cout << "Ingrese una opción: ";
        std::cin >> opcion;

        switch (opcion)
        {
        case 1:
            cargarArchivo();
            break;
        case 2:
            mostrarVideos();
            break;
        case 3:
            mostrarEpisodiosDeSerie();
            break;
        case 4:
            mostrarPeliculas();
            break;
        case 5:
            calificarVideo();
            break;
        case 0:
            std::cout << "Saliendo..." << std::endl;
            break;
        default:
            std::cout << "Opción no válida." << std::endl;
        }
    } while (opcion != 0);

    for (auto &video : videos)
    {
        delete video;
    }

    return 0;
}