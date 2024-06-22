#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark_all.hpp>

#include "topological_sort.h"

using namespace std;

TEST_CASE("Simple sort")
{
	TopologicalSorter<char> sorter;
	auto a = sorter.insertVertex('A');
	auto b = sorter.insertVertex('B');
	auto c = sorter.insertVertex('C');
	auto d = sorter.insertVertex('D');
	auto e = sorter.insertVertex('E');
	sorter.insertDirectedEdge(a, c);
	sorter.insertDirectedEdge(b, c);
	sorter.insertDirectedEdge(b, d);
	sorter.insertDirectedEdge(c, d);
	sorter.insertDirectedEdge(d, e);

    auto elements = sorter.sort();
    vector<char> vec { elements.begin(), elements.end() };
    REQUIRE(vec == vector<char> { 'B', 'A', 'C', 'D', 'E' });
}

TEST_CASE("Clothing sort")
{
	TopologicalSorter<string> sorter;
	auto undershorts = sorter.insertVertex("undershorts");
	auto pants = sorter.insertVertex("pants");
	auto belt = sorter.insertVertex("belt");
	auto shirt = sorter.insertVertex("shirt");
	auto tie = sorter.insertVertex("tie");
	auto jacket = sorter.insertVertex("jacket");
	auto socks = sorter.insertVertex("socks");
	auto shoes = sorter.insertVertex("shoes");
	auto watch = sorter.insertVertex("watch");
	sorter.insertDirectedEdge(undershorts, pants);
	sorter.insertDirectedEdge(undershorts, shoes);
	sorter.insertDirectedEdge(pants, belt);
	sorter.insertDirectedEdge(pants, shoes);
	sorter.insertDirectedEdge(belt, jacket);
	sorter.insertDirectedEdge(shirt, tie);
	sorter.insertDirectedEdge(shirt, belt);
	sorter.insertDirectedEdge(tie, jacket);
	sorter.insertDirectedEdge(socks, shoes);

    auto elements = sorter.sort();
    vector<string> vec { elements.begin(), elements.end() };
    REQUIRE(vec == vector<string> { "watch", "socks", "shirt", "tie", "undershorts", "pants", "shoes", "belt", "jacket" });
}
