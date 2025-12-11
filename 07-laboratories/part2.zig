const std = @import("std");
const fs = std.fs;
const mem = std.mem;
const fmt = std.fmt;
const allocator = std.heap.page_allocator;

const ArrayList = std.ArrayList;
const AutoHashMap = std.AutoHashMap;
const BUFF_MAX = 40_000;

// fn contains(ls: ArrayList(usize), needle: usize) bool {
//     for (ls.items) |item| {
//         if (item == needle) return true;
//     }

//     return false;
// }

fn findSplits(grid: [][]u8) !u64 {
    var total_cnt: u64 = 0;

    var beams: AutoHashMap(usize, u64) = AutoHashMap(usize, u64).init(allocator);
    defer beams.deinit();

    const start: usize = mem.indexOf(u8, grid[0], "S").?;
    try beams.put(start, 1);

    for (1..grid.len) |i| {
        var new_beams: AutoHashMap(usize, u64) = AutoHashMap(usize, u64).init(allocator);
        defer new_beams.deinit();

        var it = beams.iterator();
        while (it.next()) |kv| {
            const j = kv.key_ptr.*;
            const cnt = kv.value_ptr.*;

            if (grid[i][j] == '.') {
                if (!new_beams.contains(j)) {
                    try new_beams.put(j, 0);
                }
                new_beams.getPtr(j).?.* += cnt;
            } else if (grid[i][j] == '^') {
                if (!new_beams.contains(j + 1)) {
                    try new_beams.put(j + 1, 0);
                }
                new_beams.getPtr(j + 1).?.* += cnt;

                if (!new_beams.contains(j - 1)) {
                    try new_beams.put(j - 1, 0);
                }
                new_beams.getPtr(j - 1).?.* += cnt;
            }
        }

        beams.clearRetainingCapacity();
        var new_it = new_beams.iterator();
        while (new_it.next()) |new_kv| {
            try beams.put(new_kv.key_ptr.*, new_kv.value_ptr.*);
        }
    }

    var it = beams.iterator();
    while (it.next()) |kv| {
        total_cnt += kv.value_ptr.*;
    }

    return total_cnt;
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
