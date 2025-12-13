const std = @import("std");
const fs = std.fs;
const mem = std.mem;
const fmt = std.fmt;

const allocator = std.heap.page_allocator;
const ArrayList = std.ArrayList;
const Point = [2]i64;

const BUFF_MAX = 10_000;

pub fn main() !void {
    // const input = try fs
    //     .cwd()
    //     .openFile("./test.txt", .{ .mode = .read_only });
    const input = try fs
        .cwd()
        .openFile("./input.txt", .{ .mode = .read_only });

    var buffer: [BUFF_MAX]u8 = undefined;
    const bytes_read = try input.read(&buffer);
    const data = buffer[0..bytes_read];

    var points: ArrayList(Point) = ArrayList(Point).empty;
    defer points.deinit(allocator);

    var lines = mem.splitScalar(u8, data, '\n');
    while (lines.next()) |line| {
        if (line.len == 0) break;

        var point: Point = undefined;
        var it = mem.splitScalar(u8, line, ',');
        point[0] = try fmt.parseInt(i64, it.next().?, 10);
        point[1] = try fmt.parseInt(i64, it.next().?, 10);

        try points.append(allocator, point);
    }

    var max_area: u64 = 0;

    for (0..points.items.len) |i| {
        for (i + 1..points.items.len) |j| {
            const dx: u64 = @abs(points.items[i][0] - points.items[j][0]) + 1;
            const dy: u64 = @abs(points.items[i][1] - points.items[j][1]) + 1;

            if (dy == 0) {
                max_area = @max(max_area, dx);
            } else if (dx == 0) {
                max_area = @max(max_area, dy);
            } else {
                max_area = @max(max_area, dx * dy);
            }
        }
    }

    std.debug.print("Final result: {d}\n", .{max_area});
}
