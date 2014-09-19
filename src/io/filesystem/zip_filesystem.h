/*
 * Copyright (C) 2002-2005, 2007-2009, 2013 by the Widelands Development Team
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 */

#ifndef WL_IO_FILESYSTEM_ZIP_FILESYSTEM_H
#define WL_IO_FILESYSTEM_ZIP_FILESYSTEM_H

#include <cstring>
#include <string>

#include "base/macros.h"
#include "io/filesystem/filesystem.h"
#include "io/streamread.h"
#include "io/streamwrite.h"
#include "third_party/minizip/unzip.h"
#include "third_party/minizip/zip.h"

class ZipFilesystem : public FileSystem {
public:
	explicit ZipFilesystem(const std::string &);
	virtual ~ZipFilesystem();

	bool IsWritable() const override;

	std::set<std::string> ListDirectory(const std::string& path) override;

	bool IsDirectory(const std::string & path) override;
	bool FileExists (const std::string & path) override;

	void * Load(const std::string & fname, size_t & length) override;

	virtual void write
		(const std::string & fname, void const * data, int32_t length) override;
	void EnsureDirectoryExists(const std::string & dirname) override;
	void   MakeDirectory      (const std::string & dirname) override;

	virtual StreamRead  * OpenStreamRead
		(const std::string & fname) override;
	virtual StreamWrite * OpenStreamWrite
		(const std::string & fname) override;

	FileSystem * MakeSubFileSystem(const std::string & dirname) override;
	FileSystem * CreateSubFileSystem(const std::string & dirname, Type) override;
	void Unlink(const std::string & filename) override;
	void Rename(const std::string &, const std::string &) override;

	unsigned long long DiskSpace() override;

	static FileSystem * CreateFromDirectory(const std::string & directory);

	std::string getBasename() override {return m_zipfilename;}

protected:
	void m_OpenUnzip();
	void m_OpenZip();
	void m_Close();
	std::string strip_basename(std::string);

	enum State {
		STATE_IDLE,
		STATE_ZIPPING,
		STATE_UNZIPPPING
	};

	State       m_state;
	zipFile     m_zipfile;
	unzFile     m_unzipfile;
	/// if true data is in a directory named as the zipfile. This is set by
	/// strip_basename()
	bool        m_oldzip;
	std::string m_zipfilename;
	std::string m_basenamezip;
	std::string m_basename;

	struct ZipStreamRead : StreamRead {
		explicit ZipStreamRead(zipFile file, ZipFilesystem* zipfs);
		virtual ~ZipStreamRead();
		size_t data(void* data, size_t bufsize) override;
		bool end_of_file() const override;
	private:
		zipFile m_unzipfile;
		ZipFilesystem* m_zipfs;
	};
	struct ZipStreamWrite : StreamWrite {
		explicit ZipStreamWrite(zipFile file, ZipFilesystem* zipfs);
		virtual ~ZipStreamWrite();
		void data(const void* const data, size_t size) override;
	private:
		zipFile m_zipfile;
		ZipFilesystem* m_zipfs;
	};

};



#endif  // end of include guard: WL_IO_FILESYSTEM_ZIP_FILESYSTEM_H
