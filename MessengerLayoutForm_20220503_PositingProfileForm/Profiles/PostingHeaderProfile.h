// PostingHeaderProfile.h
#ifndef _POSTINGHEADERPROFILE_H
#define _POSTINGHEADERPROFILE_H
#include "Profile.h"

namespace parkcom {
	class Kategori;
	class PostingHeaderProfile : public Profile {
	public:
		class Builder {
			friend PostingHeaderProfile;
		public:
			Builder() {

			}
			~Builder() {

			}

			Builder* Kategori(string kategori) {
				this->kategori = kategori;
				return this;
			}
			Builder* Title(string title) {
				this->title = title;
				return this;
			}
			Builder* AttachmentImageUrl(string attachmentImageUrl) {
				this->attachmentImageUrl = attachmentImageUrl;
				return this;
			}
			Builder* Writer(string writer) {
				this->writer = writer;
				return this;
			}
			Builder* WriterGrade(string writerGrade) {
				this->writerGrade = writerGrade;
				return this;
			}
			Builder* WritedAt(string writedAt) {
				this->writedAt = writedAt;
				return this;
			}
			Builder* Views(string views) {
				this->views = views;
				return this;
			}
			PostingHeaderProfile* Build() {
				return new PostingHeaderProfile(*this);
			}

		private:
			string kategori;
			string title;
			string attachmentImageUrl;
			string writer;
			string writerGrade;
			string writedAt;		// 일자 / 시간 나누어서 그리기
			string views;
		};

	public:
		PostingHeaderProfile();
		PostingHeaderProfile(string kategori, string title, string attachmentImageUrl, string writer, string writerGrade, string writedAt, string views);
		PostingHeaderProfile(const PostingHeaderProfile& source);
		PostingHeaderProfile(Builder builder);
		virtual ~PostingHeaderProfile();
		PostingHeaderProfile& operator=(const PostingHeaderProfile& source);

		virtual void Accept(DrawingGenerator* drawingGenerator);
		virtual Profile* Clone();

		Kategori* GetKategori();
		string GetTitle();
		string GetAttachmentImageUrl();
		string GetWriter();
		string GetWriterGrade();
		string GetWritedAt();
		string GetViews();

		virtual void Repair(int kategoriState);

	private:
		Kategori* kategori;
		string title;
		string attachmentImageUrl;
		string writer;
		string writerGrade;
		string writedAt;		// 일자 / 시간 나누어서 그리기
		string views;
	};
	inline Kategori* PostingHeaderProfile::GetKategori() {
		return this->kategori;
	}
	inline string PostingHeaderProfile::GetTitle() {
		return this->title;
	}
	inline string PostingHeaderProfile::GetAttachmentImageUrl() {
		return this->attachmentImageUrl;
	}
	inline string PostingHeaderProfile::GetWriter() {
		return this->writer;
	}
	inline string PostingHeaderProfile::GetWriterGrade() {
		return this->writerGrade;
	}
	inline string PostingHeaderProfile::GetWritedAt() {
		return this->writedAt;
	}
	inline string PostingHeaderProfile::GetViews() {
		return this->views;
	}
}

#endif // _POSTINGHEADERPROFILE_H