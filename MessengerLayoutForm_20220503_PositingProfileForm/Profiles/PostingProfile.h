// PostingProfile.h
#ifndef _POSTINGPROFILE_H
#define _POSTINGPROFILE_H
#include "Profile.h"

namespace parkcom {
	class Kategori;
	class PostingProfile : public Profile {
	public:
		class Builder {
			friend PostingProfile;
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
			Builder* CommentCount(string commentCount) {
				this->commentCount = commentCount;
				return this;
			}
			Builder* Writer(string writer) {
				this->writer = writer;
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

			PostingProfile* Build() {
				return new PostingProfile(*this);
			}

		private:
			string kategori;
			string title;
			string commentCount;
			string writer;
			string writedAt;
			string views;
		};

	public:
		PostingProfile();
		PostingProfile(string kategori, string title, string commentCount, string writer, string writedAt, string views);
		PostingProfile(const PostingProfile& source);
		PostingProfile(Builder builder);
		virtual ~PostingProfile();
		PostingProfile& operator=(const PostingProfile& source);

		virtual void Accept(DrawingGenerator* drawingGenerator);
		virtual Profile* Clone();

		virtual Kategori* GetKategori();
		virtual string GetTitle();
		virtual string GetCommentCount();
		virtual string GetWriter();
		virtual string GetWritedAt();
		virtual string GetViews();

		virtual void Repair(int kategoriState);

	private:
		Kategori* kategori;
		string title;
		string commentCount;
		string writer;
		string writedAt;	// 작성일자
		string views;
	};

	inline Kategori* PostingProfile::GetKategori() {
		return this->kategori;
	}
	inline string PostingProfile::GetTitle() {
		return this->title;
	}
	inline string PostingProfile::GetCommentCount() {
		return this->commentCount;
	}
	inline string PostingProfile::GetWriter() {
		return this->writer;
	}
	inline string PostingProfile::GetWritedAt() {
		return this->writedAt;
	}
	inline string PostingProfile::GetViews() {
		return this->views;
	}
}

#endif // _POSTINGPROFILE_H