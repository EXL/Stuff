/*
 * About:
 *   A simple utility to renaming photos and videos captured on Motorola devices to my own file naming format.
 *
 * Author:
 *   EXL
 *
 * License:
 *   MIT
 *
 * History:
 *   11-Oct-2022: Created initial version.
 *
 * Usage:
 *   > renamer %mode% %input% %output%
 *
 * Examples:
 *   > renamer dir C:\Photos C:\OutPhotos
 *   > renamer file C:\Photos\List.txt C:\OutPhotos\List.txt
 */

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFileInfoList>
#include <QMap>
#include <QMapIterator>
#include <QString>
#include <QStringList>
#include <QTextStream>

#include <cstdio>
#include <cstdlib>

enum ARGUMENTS {
	ARGUMENT_APPLICATION,
	ARGUMENT_MODE,
	ARGUMENT_INPUT,
	ARGUMENT_OUTPUT
};

static const char *MODE_DIR = "dir";
static const char *MODE_FILE = "file";

static const char *IMG_PREFIX_FILENAME = "IMGM";
static const char *IMG_EXTENS_FILENAME = ".jpg";
static const char *VID_PREFIX_FILENAME = "VIDM";
static const char *VID_EXTENS_FILENAME = ".mp4";

static QMap<QString, QString> names_table;
static QStringList all_file_names;

static bool is_d2_format(const QString &filename) {
	const QStringList string_list = filename.split("-");
	const QString first_token = string_list[0];
	bool ok = false;
	first_token.toInt(&ok);
	return ok && (first_token.length() == 4);
}

static bool is_d4_and_pq_format(const QString &filename) {
	if (!filename.startsWith("IMG_") && !filename.startsWith("VID_"))
		return false;
	const QStringList string_list = filename.split("_");
	const QString first_token = string_list[0];
	const QString second_token = string_list[1];
	bool ok = false;
	second_token.toInt(&ok);
	return ok && (second_token.length() == 8);
}

static QString get_month(const QString &month) {
	const int mmm = month.toInt();
	switch (mmm) {
		case  1: return "Jan";
		case  2: return "Feb";
		case  3: return "Mar";
		case  4: return "Apr";
		case  5: return "May";
		case  6: return "Jun";
		case  7: return "Jul";
		case  8: return "Aug";
		case  9: return "Sep";
		case 10: return "Oct";
		case 11: return "Nov";
		case 12: return "Dec";
	}
	return QString::null;
}

static QString create_new_filename_from_d2_format(const QString &old_filename) {
	// 2020-09-22_17-49-19_59.jpg
	// 2020-09-22_17-50-23_653.jpg
	// 2020-09-22_19-01-07_950.jpg
	const QStringList string_list = old_filename.split("_");
	if (string_list.length() != 3)
		return QString::null;

	const QStringList date_list = string_list[0].split("-");
	if (date_list.length() != 3)
		return QString::null;

	const QStringList time_list = string_list[1].split("-");
	if (time_list.length() != 3)
		return QString::null;

	// IMGM_09-Nov-2020_06-00_01.jpg
	return
		QString("%1_%2-%3-%4_%5-%6_")
			.arg(IMG_PREFIX_FILENAME)
			.arg(date_list[2])
			.arg(get_month(date_list[1]))
			.arg(date_list[0])
			.arg(time_list[0])
			.arg(time_list[1]);
}

static QString create_new_filename_from_d4_and_pq_format(const QString &old_filename) {
	// IMG_20200904_193014_316.jpg
	// IMG_20200905_132602_002.jpg
	// IMG_20200927_122939_834.jpg
	const QStringList string_list = old_filename.split("_");
	if (string_list.length() != 4)
		return QString::null;

	QString prefix(IMG_PREFIX_FILENAME);
	if (string_list[0] == "IMG")
		prefix = IMG_PREFIX_FILENAME;
	else if (string_list[0] == "VID")
		prefix = VID_PREFIX_FILENAME;

	const QString date_d = string_list[1].mid(6, 2);
	const QString date_m = string_list[1].mid(4, 2);
	const QString date_y = string_list[1].mid(0, 4);

	const QString time_s = string_list[2].mid(4, 2);
	const QString time_m = string_list[2].mid(2, 2);
	const QString time_h = string_list[2].mid(0, 2);

	Q_UNUSED(time_s);

	// IMGM_09-Nov-2020_06-00_01.jpg
	return
		QString("%1_%2-%3-%4_%5-%6_")
			.arg(prefix)
			.arg(date_d)
			.arg(get_month(date_m))
			.arg(date_y)
			.arg(time_h)
			.arg(time_m);
}

static QString generate_new_filename(const QString &old_filename) {
	if (is_d2_format(old_filename))
		return create_new_filename_from_d2_format(old_filename);
	else if (is_d4_and_pq_format(old_filename))
		return create_new_filename_from_d4_and_pq_format(old_filename);
	else
		return QString::null;
}

static QString generate_unique_filename(const QString &original_filename, const QString &old_filename) {
	if (old_filename == QString::null)
		return QString::null;

	const int size = all_file_names.size();
	int count = 0;
	for (int i = 0; i < size; ++i)
		if (old_filename == all_file_names.at(i))
			count++;

	if (count == 0)
		return QString::null;

	QString ext(IMG_EXTENS_FILENAME);
	if (original_filename.endsWith(".jpg"))
		ext = IMG_EXTENS_FILENAME;
	else if (original_filename.endsWith(".mp4"))
		ext = VID_EXTENS_FILENAME;

	return old_filename + ((count > 9) ? QString::number(count) : "0" + QString::number(count)) + ext;
}

static void fill_names_table(const QDir &input_directory) {
	QFileInfoList files = input_directory.entryInfoList();
	const int size = files.size();
	for (int i = 0; i < size; ++i) {
		const QFileInfo file_info = files.at(i);
		const QString filename = file_info.fileName();
		const QString renamed = generate_new_filename(filename);
		all_file_names.append(renamed);
		names_table.insert(filename, generate_unique_filename(filename, renamed));
	}
}

static void fill_names_table(QFile &input_file) {
	QTextStream stream(&input_file);
	while (!stream.atEnd()) {
		const QString line = stream.readLine();
		const QString renamed = generate_new_filename(line);
		if (renamed != QString::null) {
			all_file_names.append(renamed);
			names_table.insert(line, generate_unique_filename(line, renamed));
		}
	}
}

static void copy_files(const QDir &input_directory, const QDir &output_directory) {
	QMapIterator<QString, QString> iterator(names_table);
	for (int i = 0; iterator.hasNext(); ++i) {
		iterator.next();

		const QString original = iterator.key();
		const QString renamed = iterator.value();

		if (renamed != QString::null) {
			QFile::copy(
				input_directory.absolutePath() + QDir::separator() + original,
				output_directory.absolutePath() + QDir::separator() + renamed
			);
		}

		fprintf(
			stderr,
			"Rename [%d]: %s => %s\n",
			i + 1,
			original.toStdString().c_str(),
			(renamed != QString::null) ? (renamed + "!").toStdString().c_str() : "Unknown filename format, skipped."
		);
	}
}

static void write_file(QFile &input_file, QFile &output_file) {
	QTextStream input_stream(&input_file);
	QTextStream output_stream(&output_file);

	input_stream.seek(0);

	int count = 0;
	while (!input_stream.atEnd()) {
		const QString line = input_stream.readLine();
		const QString replaced = names_table.value(line, line);

		output_stream << replaced << "\n";
		if (replaced != line) {
			count++;
			fprintf(
				stderr,
				"Replaced [%d] %s => %s!\n",
				count,
				line.toStdString().c_str(),
				replaced.toStdString().c_str()
			);
		}
	}
}

static int handle_directories(const char *input, const char *output) {
	QDir input_directory(input);
	if (!input_directory.exists()) {
		fprintf(stderr, "Error: Input directory '%s' isn't exist!\n", input);
		return EXIT_FAILURE;
	}
	const QDir output_directory(output);
	if (!output_directory.exists()) {
		fprintf(stderr, "Error: Output directory '%s' isn't exist!\n", output);
		return EXIT_FAILURE;
	}

	input_directory.setFilter(QDir::Files | QDir::Readable | QDir::Hidden | QDir::System | QDir::NoSymLinks);

	fill_names_table(input_directory);
	copy_files(input_directory, output_directory);

	return EXIT_SUCCESS;
}

static int handle_file(const char *input, const char *output) {
	QFile input_file(input);
	if (!input_file.exists()) {
		fprintf(stderr, "Error: Input file '%s' isn't exist!\n", input);
		return EXIT_FAILURE;
	}
	if (!input_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		fprintf(stderr, "Error: Cannot open input file '%s' for reading!\n", input);
		return EXIT_FAILURE;
	}
	QFile output_file(output);
	if (!output_file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		fprintf(stderr, "Error: Cannot open output file '%s' for writing!\n", output);
		return EXIT_FAILURE;
	}

	fill_names_table(input_file);
	write_file(input_file, output_file);

	output_file.close();
	input_file.close();

	return EXIT_SUCCESS;
}

int main(int argc, char *argv[]) {
	if (argc != 4) {
		fprintf(stderr, "Error: Wrong argument count!\n\n");
		fprintf(stderr, "Usage:\n\trenamer %mode% %input% %output%\n\n");
		fprintf(stderr, "Examples:\n\trenamer dir C:\\Photos C:\\OutPhotos\n");
		fprintf(stderr, "\trenamer file C:\\Photos\\List.txt C:\\OutPhotos\\List.txt\n\n");
		return EXIT_FAILURE;
	}

	const QString mode(argv[ARGUMENT_MODE]);
	if (mode == MODE_DIR)
		return handle_directories(argv[ARGUMENT_INPUT], argv[ARGUMENT_OUTPUT]);
	else if (mode == MODE_FILE)
		return handle_file(argv[ARGUMENT_INPUT], argv[ARGUMENT_OUTPUT]);
	else
		fprintf(stderr, "Error: Unknown mode!\n");

	return EXIT_FAILURE;
}
