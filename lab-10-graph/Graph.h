#pragma once

#include <algorithm>
#include <limits>
#include <stdexcept>
#include <iostream>

template<typename TVertex, typename TEdge>
class Graph {

public:
    /*
     * Структура ребра в списке смежности.
     */
    struct Edge {
        TVertex dstVertex;//в какую вершину ведет ребро
        TEdge edge;//значение ребра

        Edge(TVertex dstVertex, TEdge edge) : dstVertex(dstVertex), edge(edge){;}
    };

private:

    /*
     * Узел списка в списке смежности.
     */
    struct EdgeNode {
        Edge edge;//информация о ребре
        EdgeNode *next;//следующий элемент

        EdgeNode(Edge edge, EdgeNode *next) : edge(edge), next(next) {}
    };

    /*
     * Структура веришины в массиве вершин.
     */
    struct Vertex {
        TVertex vertex;//значение
        EdgeNode *edges;//список смежности

        Vertex() : edges(nullptr) {}

        explicit Vertex(TVertex vertex) : vertex(vertex), edges(nullptr) {}
    };

    Vertex *_graph;//массив вершин графа
    std::size_t _count;//количество вершин

    /*
     * Получение индекса вершины без генерации исключения.
     *
     * @param vertex Значение вершины.
     * @return Индекс вершины или количество веришны, в случае её отсутствия.
     */
    std::size_t GetVertexIndex(TVertex vertex) const {
        for (std::size_t i = 0; i < _count; ++i) {
            if (_graph[i].vertex == vertex) {
                return i;
            }
        }
        return _count;
    }

    /*
     * Проход по списку смежности вершины и удаление ребер, ведущих в вершину vertex.
     *
     * @param vertex Значение удаляемой вершины.
     * @param index Индекс вершины, из списка смежности которой необходимо удалять ребра.
     */
    void EraseVertexFromList(TVertex vertex,  size_t index){
        auto head = _graph[index].edges;
        if(head) {
            if (head->edge.dstVertex == vertex) {
                _graph[index].edges = EraseElement(head);
            } else {
                while (head->next) {
                    if (head->next->edge.dstVertex == vertex) {
                        head->next = EraseElement(head->next);
                        break;
                    } else {
                        head = head->next;
                    }
                }
            }
        }
    }

    /*
     * Удаление узла из списка.
     *
     * @param ptr Удаляемый узел.
     * @return Узел, стоящий после удаляемого.
     */
    EdgeNode* EraseElement(EdgeNode* ptr){
        auto temp = ptr->next;
        delete ptr;
        return temp;
    }

public:
    /*
     * Конструктор по умолчанию.
     */
    Graph() : _graph(nullptr), _count(0) {}

    /*
     * Запрещенный конструктор копирования.
     */
    Graph(const Graph &) = delete;

    /*
     * Запрещенный оператор присваивания копированием.
     */
    Graph &operator=(const Graph &) = delete;

    /*
     * Деструктор.
     */
    ~Graph() {
       Clear();
    }

    /*
     * Получение индекса вершины с генерацией исключения, в случае её отсутствия.
     *
     * @param vertex Значение веришны.
     * @return Индекс вершины.
     */
    size_t GetVertexIndexOrThrow(TVertex vertex) const {
        const auto index = GetVertexIndex(vertex);
        if (index == _count)
            throw std::invalid_argument("Vertex not found!");
        return index;
    }

    /*
     * Получение количества вершин.
     *
     * @return Количество вершин в графе.
     */
    [[nodiscard]] std::size_t GetVertexCount() const {
        return _count;
    }

    /*
     * Получение значения вершины из графа.
     *
     * @param index Индекс получаемой веришны в графе.
     * @return Вершина.
     */
    TVertex GetVertex(std::size_t index) const {
        return _graph[index].vertex;
    }

    /*
     * Добавление вершины в граф.
     *
     * @param vertex Значение вершины, добавляемой в граф.
     */
    void AddVertex(TVertex vertex) {
        const auto index = GetVertexIndex(vertex);
        if (index != _count)
            throw std::invalid_argument("Vertex already exists!");
        auto graph = new Vertex[_count + 1];
        for (std::size_t i = 0; i < _count; ++i) {
            graph[i] = _graph[i];
        }
        graph[_count] = Vertex(vertex);
        delete[] _graph;
        _graph = graph;
        ++_count;
    }

    /*
     * Добавление ребра в граф.
     *
     * @param srcVertex Из какой вершины.
     * @param dstVertex В какую вершину.
     * @param edge Значение ребра.
     */
    void AddEdge(TVertex srcVertex, TVertex dstVertex, TEdge edge) {
        if (srcVertex != dstVertex) {
            const auto srcIndex = GetVertexIndexOrThrow(srcVertex);
            Edge e(dstVertex, edge);
            _graph[srcIndex].edges = new EdgeNode(e, _graph[srcIndex].edges);
        }
        else {
            throw std::invalid_argument("This edge can not be created!");
        }
    }

    /*
     * Получение количетсва ребер у вершины.
     *
     * @param srcVertex Из какой вершины.
     * @return Количество ребер.
     */
    std::size_t GetEdgeCount(TVertex srcVertex) const {
        std::size_t count = 0;
        auto node = _graph[GetVertexIndexOrThrow(srcVertex)].edges;
        while (node) {
            ++count;
            node = node->next;
        }
        return count;
    }

    /*
     * Получение информации о ребре.
     *
     * @param srcVertex Из какой веришны
     * @param index  Индекс ребра в списке смежности.
     * @return Информация о ребре.
     */
    Edge GetEdge(TVertex srcVertex, std::size_t index) const {
        auto node = _graph[GetVertexIndexOrThrow(srcVertex)].edges;
        for (size_t i = 0; i < index; ++i)
            node = node->next;
        return node->edge;
    }

    /*
     * Отладочный вывод графа на экран.
     */
    void Print() const{
        for(size_t i = 0; i < _count; ++i) {
            std::cout << _graph[i].vertex;
            EdgeNode* head = _graph[i].edges;
            while(head){
                std::cout << "-->";
                std::cout<< "(" << head->edge.dstVertex <<"; " << head->edge.edge << ")";
                head = head->next;
            }
            std::cout << "--|" << std::endl;
        }
    }

    /*
     * Редактирование вершины.
     *
     * @param vertex Исходное значение веришны.
     * @param newValue Новое значение, которое будет установлено.
     */
    void EditVertex(TVertex vertex, TVertex newValue){
        if(GetVertexIndex(newValue) != _count){
            throw std::invalid_argument("Vertex already exist!");
        }

        size_t index = GetVertexIndexOrThrow(vertex);
        _graph[index].vertex = newValue;

        for(size_t i = 0; i < _count; ++i) {
            EdgeNode *head = _graph[i].edges;

            while(head){
                if(head->edge.dstVertex == vertex){
                    head->edge.dstVertex = newValue;
                }
                head = head->next;
            }
        }
    }

    /*
     * Редактирование ребра.
     *
     * @param src Из какой вершины выходит ребро.
     * @param dst В какую вершину ведет ребро.
     * @param newEdge Новое значение ребра.
     */
    void EditEdge(TVertex src, TVertex dst, TEdge newEdge){
        size_t index = GetVertexIndexOrThrow(src);
        EdgeNode* head = _graph[index].edges;

        while(head){
            if(head->edge.dstVertex == dst){
                head->edge.edge = newEdge;
                return;
            }
            head = head->next;
        }

        throw std::invalid_argument("This edge does not exist!");

    }

    /*
     * Удаление вершины.
     *
     * @param vertex Значение удаляемой вершины.
     */
    void EraseVertex(TVertex vertex){
        GetVertexIndexOrThrow(vertex);
        auto graph = new Vertex[_count - 1];
        //индекс обхода нового массива.
        size_t k = 0;
        for(size_t i = 0; i < _count; ++i, ++k){

            if(_graph[i].vertex == vertex){
                auto head = _graph[i].edges;
                while(head){
                    head = EraseElement(head);
                }
                --k;

            }
            else {
                graph[k] = _graph[i];
            }
        }
        delete _graph;
        _graph = graph;
        --_count;

        for(size_t i = 0; i < _count; ++i) {
            EraseVertexFromList(vertex, i);
        }
    }


    /*
     * Удаление ребра.
     *
     * @param src Из какой вершины выходит ребро.
     * @param dst В какую вершину ведет ребро.
     */
    void EraseEdge(TVertex src, TVertex dst){
        auto index = GetVertexIndexOrThrow(src);
        EraseVertexFromList(dst, index);
    }

    /*
     * Очистка графа.
     */
    void Clear(){

       while(GetVertexCount() != 0){
           EraseVertex(_graph[0].vertex);
       }
    }
};


/*
 * Рекурсивный обход графа в глубину.
 *
 * @param graph Структура графа.
 * @param begin Начальная веришна для обхода.
 * @param f Функционал, который будет применен для каждой посещенной вершины.
 * @param visited Массив посещенных веришн.
 */
template<typename TVertex, typename TEdge, typename TFunctional>
void RDepthFirstSearch(const Graph<TVertex, TEdge> &graph, TVertex begin, TFunctional f, bool* visited){
    try {
        f(begin);
        visited[graph.GetVertexIndexOrThrow(begin)] = true;
        for (size_t i = 0; i < graph.GetEdgeCount(begin); ++i) {
            auto j = graph.GetEdgeCount(begin);
            if (!visited[graph.GetVertexIndexOrThrow(graph.GetEdge(begin, i).dstVertex)]) {
                RDepthFirstSearch(graph, graph.GetEdge(begin, i).dstVertex, f, visited);
            }
        }
    }
    catch(...){
        delete[] visited;
        throw;
    }

}

/*
 * Итеративный обход графа в глубину.
 *
 * @param graph Структура графа.
 * @param begin Начальная вершины для обхода.
 * @param f Функционал, который будет применен для каждой посещенной вершины.
 */
template<typename TVertex, typename TEdge, typename TFunctional>
void DepthFirstSearch(const Graph<TVertex, TEdge> &graph, TVertex begin, TFunctional f) {
    const auto n = graph.GetVertexCount();
    auto visited = new bool[n];
    auto stack = new std::size_t[n];
    std::size_t stackSize = 0;
    for (std::size_t i = 0; i < n; ++i) {
        visited[i] = false;
    }

    try {
        const auto beginIndex = graph.GetVertexIndexOrThrow(begin);
        stack[stackSize++] = beginIndex;
        visited[beginIndex] = true;

        while (stackSize > 0) {
            const auto vertexIndex = stack[--stackSize];
            const auto vertex = graph.GetVertex(vertexIndex);
            f(vertex);
            const auto edgeCount = graph.GetEdgeCount(vertex);
            for (std::size_t edgeIndex = 0; edgeIndex < edgeCount; ++edgeIndex) {
                const auto dstIndex = graph.GetVertexIndexOrThrow(graph.GetEdge(vertex, edgeIndex).dstVertex);
                if (!visited[dstIndex]) {
                    stack[stackSize++] = dstIndex;
                    visited[dstIndex] = true;
                }
            }

        }
    }
    catch (...) {
        delete[] visited;
        delete[] stack;
        throw;
    }
    delete[] visited;
    delete[] stack;
}

/*
 * Итеративный обход графа в ширину.
 *
 * @param graph Структура графа.
 * @param begin Начальная вершины для обхода.
 * @param f Функционал, который будет применен для каждой посещенной вершины.
 */
template<typename TVertex, typename TEdge, typename TFunctional>
void BreadthFirstSearch(const Graph<TVertex, TEdge> &graph, TVertex begin, TFunctional f) {
    const auto n = graph.GetVertexCount();
    auto visited = new bool[n];
    auto queue = new std::size_t[n];
    std::size_t push = 0;
    std::size_t pop = 0;
    for (std::size_t i = 0; i < n; ++i) {
        visited[i] = false;
    }

    try {
        const auto beginIndex = graph.GetVertexIndexOrThrow(begin);
        queue[push++] = beginIndex;
        visited[beginIndex] = true;

        while (push != pop) {
            const auto vertexIndex = queue[pop++];
            const auto vertex = graph.GetVertex(vertexIndex);
            f(vertex);
            const auto edgeCount = graph.GetEdgeCount(vertex);
            for (std::size_t edgeIndex = 0; edgeIndex < edgeCount; ++edgeIndex) {
                const auto dstIndex = graph.GetVertexIndexOrThrow(graph.GetEdge(vertex, edgeIndex).dstVertex);
                if (!visited[dstIndex]) {
                    queue[push++] = dstIndex;
                    visited[dstIndex] = true;
                }
            }

        }
    }
    catch (...) {
        delete[] visited;
        delete[] queue;
        throw;
    }
    delete[] visited;
    delete[] queue;
}

/*
 * Опрделяем вес ребра как float.
 */
template<typename TEdge>
struct DefaultEdgeWeight {
    float operator()(TEdge edge) {
        return static_cast<float>(edge);
    }
};

const auto INFINITY_DISTANCE = std::numeric_limits<float>::infinity();//бесконечность


/*
 * Алгоритм Дейкстры для поиска кратчайшего пути в графе.
 *
 * @param graph Структура графа.
 * @param begin Вершина начала поиска.
 * @param end Вершина конца поиска.
 * @param path Кратчайший путь от begin до end.
 * @param pathLength Длина кратчайшего пути.
 * @return Значение расстояния от begin до end.
 */
template<typename TVertex, typename TEdge, typename TEdgeWeight = DefaultEdgeWeight<TEdge>>
float Dijkstra(const Graph<TVertex,TEdge> &graph,
               TVertex begin,
               TVertex end,
               TVertex* path,
               std::size_t *pathLength) {
    const auto n = graph.GetVertexCount();
    auto d = new float[n];
    auto u = new bool[n];
    auto p = new std::size_t[n];
    for (std::size_t i = 0; i < n; ++i) {
        d[i] = INFINITY_DISTANCE;
        u[i] = false;
        p[i] = n;
    }

    try {
        const auto beginIndex = graph.GetVertexIndexOrThrow(begin);
        d[beginIndex] = 0;

        for (std::size_t i = 0; i < n; ++i) {
            // ЭТАП 1: Выбрать непомеченную вершину с минимальными расстоянием
            std::size_t selectedIndex = n;
            float selectedDistance = INFINITY_DISTANCE;
            for (std::size_t j = 0; j < n; ++j) {
                if (!u[j] && d[j] < selectedDistance) {
                    selectedIndex = j;
                    selectedDistance = d[j];
                }
            }
            if (selectedIndex == n)
                break;
            u[selectedIndex] = true;

            // ЭТАП 2: Для всех смежных ребёр выбранной вершины провести релаксацию
            const auto selectedVertex = graph.GetVertex(selectedIndex);
            const auto edgeCount = graph.GetEdgeCount(selectedVertex);
            for (std::size_t j = 0; j < edgeCount; ++j) {
                const auto edge = graph.GetEdge(selectedVertex, j);
                const auto dstVertex = edge.dstVertex;
                const auto dstIndex = graph.GetVertexIndexOrThrow(dstVertex);
                const auto distance = d[selectedIndex] + TEdgeWeight()(edge.edge);
                if (distance < d[dstIndex]) {
                    d[dstIndex] = distance;
                    p[dstIndex] = selectedIndex;
                }
            }
        }

        const auto endIndex = graph.GetVertexIndexOrThrow(end);
        const auto distance = d[endIndex];
        *pathLength = 0;
        if (distance != INFINITY_DISTANCE && path != nullptr) {
            auto currentIndex = endIndex;
            while (currentIndex != beginIndex) {
                path[(*pathLength)++] = graph.GetVertex(currentIndex);
                currentIndex = p[currentIndex];
            }
            path[(*pathLength)++] = begin;
            std::reverse(path, path + *pathLength);
        }
        delete[] d;
        delete[] u;
        delete[] p;
        return distance;
    }
    catch (...) {
        delete[] d;
        delete[] u;
        delete[] p;
        throw;
    }
}

/*
 * Алгоритм Беллмана-Форда для поиска кратчайшего пути в графе.
 *
 * @param graph Структура графа.
 * @param begin Вершина начала поиска.
 * @param end Вершина конца поиска.
 * @param path Кратчайший путь от begin до end.
 * @param pathLength Длина кратчайшего пути.
 * @return Значение расстояния от begin до end.
 */
template<typename TVertex, typename TEdge, typename TEdgeWeight = DefaultEdgeWeight<TEdge>>
float BellmanFord(const Graph<TVertex, TEdge> &graph,
                  TVertex begin,
                  TVertex end,
                  TVertex *path,
                  std::size_t *pathLength) {
    const auto n = graph.GetVertexCount();
    auto d = new float[n];
    auto p = new std::size_t[n];
    for (std::size_t i = 0; i < n; ++i) {
        d[i] = INFINITY_DISTANCE;
        p[i] = n;
    }

    try {
        const auto beginIndex = graph.GetVertexIndexOrThrow(begin);
        d[beginIndex] = 0;

        for (std::size_t i = 0; i < n - 1; ++i) {
            // Перебираем все рёбра!
            // Так как граф представлен списком смежности, нам нужно два цикла:
            // сначала перебираем все вершины, а уже для каждой вершины перебираем все рёбра.
            for (std::size_t vertexIndex = 0; vertexIndex < n; ++vertexIndex) {
                const auto vertex = graph.GetVertex(vertexIndex);
                const auto edgeCount = graph.GetEdgeCount(vertex);
                for (std::size_t edgeIndex = 0; edgeIndex < edgeCount; ++edgeIndex) {
                    const auto edge = graph.GetEdge(vertex, edgeIndex);
                    const auto dstVertex = edge.dstVertex;
                    const auto dstIndex = graph.GetVertexIndexOrThrow(dstVertex);
                    const auto distance = d[vertexIndex] + TEdgeWeight()(edge.edge);
                    if (distance < d[dstIndex]) {
                        d[dstIndex] = distance;
                        p[dstIndex] = vertexIndex;

                    }
                }
            }
        }

        const auto endIndex = graph.GetVertexIndexOrThrow(end);
        const auto distance = d[endIndex];
        *pathLength = 0;
        if (distance != INFINITY_DISTANCE && path != nullptr) {
            auto currentIndex = endIndex;
            while (currentIndex != beginIndex) {
                path[(*pathLength)++] = graph.GetVertex(currentIndex);
                currentIndex = p[currentIndex];
            }
            path[(*pathLength)++] = begin;
            std::reverse(path, path + *pathLength);
        }
        delete[] d;
        delete[] p;
        return distance;
    }
    catch (...) {
        delete[] d;
        delete[] p;
        throw;
    }
}
