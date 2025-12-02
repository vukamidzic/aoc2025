const std = @import("std");
const fmt = std.fmt;
const mem = std.mem;
const whitespace = std.ascii.whitespace;
const allocator = std.heap.page_allocator;

const BUFF_MAX: usize = 1024;

fn validIds(start: u64, end: u64) !u64 {
    var sum: u64 = 0;
    for (start..end + 1) |n| {
        const s = try fmt.allocPrint(allocator, "{d}", .{n});
        var found_multiple: bool = false;
        for (1..s.len) |i| {
            const pref = s[0..i];
            const occurs = mem.count(u8, s, pref);
            if (occurs * pref.len == s.len) {
                found_multiple = true;
                break;
            }
        }

        if (found_multiple) sum += @intCast(n);
    }

    return sum;
}

pub fn main() !void {
    // const input = try std.fs
    //     .cwd()
    //     .openFile("./test.txt", .{ .mode = .read_only });
    const input = try std.fs
        .cwd()
        .openFile("./input.txt", .{ .mode = .read_only });

    defer input.close();

    var buffer: [BUFF_MAX]u8 = undefined;
    const bytes_read = try input.read(&buffer);
    const data = buffer[0..bytes_read];

    var result: u64 = 0;

    var lines = mem.splitScalar(u8, data, ',');
    while (lines.next()) |line| {
        var it = mem.splitScalar(u8, mem.trim(u8, line, &whitespace), '-');
        const start = try fmt.parseInt(u64, it.next().?, 10);
        const end = try fmt.parseInt(u64, it.next().?, 10);
        result += try validIds(start, end);
    }

    std.debug.print("Final result: {d}\n", .{result});
}
