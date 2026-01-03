#include "../Solution.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <ranges>
#include <string_view>
#include <charconv>
#include <system_error>
#include <algorithm>
#include <cstdint>

struct Point {
    int x_, y_, z_;
    
    Point() = delete;
    Point(const std::string& pointStr) {
        auto coords = pointStr | std::views::split(',');
        
        auto x_sv = *coords.begin();
        auto y_sv = *(coords | std::views::drop(1)).begin();
        auto z_sv = *(coords | std::views::drop(2)).begin();
        
        auto [ptrx, ecx] = std::from_chars(x_sv.data(), x_sv.data() + x_sv.size(), x_);
        auto [ptry, ecy] = std::from_chars(y_sv.data(), y_sv.data() + y_sv.size(), y_);
        auto [ptrz, ecz] = std::from_chars(z_sv.data(), z_sv.data() + z_sv.size(), z_);
        
        if (ecx != std::errc() || ecy != std::errc() || ecz != std::errc()) {
            throw std::invalid_argument("Input is not valid!");
        }
    }
    
    float distance(const Point& other) const {
        return std::sqrt(std::pow(x_-other.x_, 2) + std::pow(y_-other.y_, 2) + std::pow(z_-other.z_, 2));
    }
    
    bool operator==(const Point& other) const {
        return (x_ == other.x_) && (y_ == other.y_) && (z_ == other.z_);
    }
    
    std::string toString() const {
        return "(" + std::to_string(x_) + "," + std::to_string(y_) + "," + std::to_string(z_) + ")";
    }
};

struct Connection {
    Point p1_, p2_;
    long double length_;
    
    Connection() = delete;
    Connection(Point p1, Point p2) : p1_(std::move(p1)), p2_(std::move(p2)), length_(p1_.distance(p2_)) {}
    
    std::string toString() const {
        return p1_.toString() + " <-> " + p2_.toString();
    }
};

struct Circuit {
    std::vector<Point> points{};
    
    Circuit() = delete;
    Circuit(const Point& first) {
        points.push_back(first);
    }
    
    bool contains(const Point& point) const {
        return std::ranges::contains(points, point);
    }
    
    size_t numPoints() const {
        return points.size();
    }
    
    std::string toString() const {
        std::string str("[");
        for (const auto& point : points) str += point.toString();
        str += "]";
        return str;
    }
};

struct JunctionBoxes : Solution {
  using Solution::Solution;

  void connect(std::vector<Circuit>::iterator circuit1_it, std::vector<Circuit>::iterator circuit2_it, std::vector<Circuit>& circuits) {
    if (circuit1_it != circuit2_it) {
      std::ranges::copy(circuit2_it->points | std::views::as_rvalue, std::back_inserter(circuit1_it->points));
      circuits.erase(circuit2_it);
    }
  }

  void solve() override {
    // parse to points
    auto points = input
        | std::views::transform([] (const std::string& pointStr) { return Point(pointStr); })
        | std::ranges::to<std::vector<Point>>();
    
    // make all possible connections and sort by distance
    std::vector<Connection> connections{};
    for (size_t i{}; i < points.size(); i++) {
        for (size_t j{i+1}; j < points.size(); j++) {
            connections.emplace_back(points.at(i), points.at(j));
        }
    }
    std::ranges::sort(connections, {}, &Connection::length_);

    for (const auto& con : connections) logger.debug("{}\n", con.toString());
    logger.debug("\n");

    // make connections in ascending order of distance
    auto circuits = points
        | std::views::transform([](const Point& point) { return Circuit(point); })
        | std::ranges::to<std::vector<Circuit>>();
    
    std::int64_t product{};
    for (const auto& con : connections) {
        for (const auto& circ : circuits) logger.debug("{}\n", circ.toString());
        logger.debug("\n");
        logger.debug("{}\n", con.toString());
        
        auto circuit1_it = std::ranges::find_if(circuits, 
            [&con](const Circuit& circuit) { return circuit.contains(con.p1_); }
        );
        auto circuit2_it = std::ranges::find_if(circuits, 
            [&con](const Circuit& circuit) { return circuit.contains(con.p2_); }
        );
        
        connect(circuit1_it, circuit2_it, circuits);

        if (circuits.size() == 1) {
          logger.info("{}\n", con.toString());
          for (const auto& circ : circuits) logger.info("{}\n", circ.toString());
          logger.info("\n");

          product = static_cast<std::int64_t>(con.p1_.x_) * static_cast<std::int64_t>(con.p2_.x_);
          break;
        }
    }
    for (const auto& circ : circuits) logger.debug("{}\n", circ.toString());
    logger.debug("\n");
    
    logger.info("final product: {}", product);
  }
};

int main() {
  JunctionBoxes("input.txt").solve();
}
