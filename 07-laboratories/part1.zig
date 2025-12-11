const std = @import("std");
const fs = std.fs;
const mem = std.mem;
const fmt = std.fmt;
const allocator = std.heap.page_allocator;

const ArrayList = std.ArrayList;
const BUFF_MAX = 40_000;

fn contains(ls: ArrayList(usize), needle: usize) bool {
    for (ls.items) |item| {
        if (item == needle) return true;
    }

    return false;
}

fn findSplits(grid: [][]u8) !u64 {
    var cnt: u64 = 0;

    var beams: ArrayList(usize) = ArrayList(usize).empty;
    const start: usize = mem.indexOf(u8, grid[0], "S").?;
    try beams.append(allocator, start);

    for (1..grid.len) |i| {
        var new_beams: ArrayList(usize) = ArrayList(usize).empty;
        defer new_beams.deinit(allocator);

        for (beams.items) |j| {
            if (grid[i][j] == '.') {
                if (!contains(new_beams, j)) {
                    try new_beams.append(allocator, j);
                    grid[i][j] = '|';
                }
            } else if (grid[i][j] == '^') {
                cnt += 1;
                if (!contains(new_beams, j + 1)) {
                    try new_beams.append(allocator, j + 1);
                    grid[i][j + 1] = '|';
                }
                if (!contains(new_beams, j - 1)) {
                    try new_beams.append(allocator, j - 1);
                    grid[i][j - 1] = '|';
                }
            }
        }

        beams.clearRetainingCapacity();
        try beams.appendSlice(allocator, new_beams.items);
    }

    return cnt;
}

pub fn main() !void {
    // const input = try fs
    //     .cwd()
    //     .openFile("./test.txt", .{ .mode = .read_only });
    const input = try fs
        .cwd()
        .openFile("./input.txt", .{ .mode = .read_only });
    defer input.close();

    var buffer: [BUFF_MAX]u8 = undefined;
    const bytes_read = try input.read(&buffer);
    const data = buffer[0..bytes_read];

    var arr: ArrayList([]u8) = ArrayList([]u8).empty;
    defer arr.deinit(allocator);

    var lines = mem.splitScalar(u8, data, '\n');
    while (lines.next()) |line| {
        if (line.len == 0) break;
        try arr.append(allocator, @constCast(line));
    }

    const grid: [][]u8 = arr.items;
    const result = try findSplits(grid);
    std.debug.print("Final result: {d}\n", .{result});
}
