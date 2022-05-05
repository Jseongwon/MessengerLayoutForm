// PostingCommentProfile.h
#ifndef _POSTINGCOMMENTPROFILE_H
#define _POSTINGCOMMENTPROFILE_H
#include "Profile.h"

namespace parkcom {
	class PostingCommentProfile : public Profile {
	public:
		class Builder {
			friend PostingCommentProfile;
		public:
			Builder() {

			}
			~Builder() {

			}

			Builder* AttachmentImageUrl(string attachmentImageUrl) {
				this->attachmentImageUrl = attachmentImageUrl;
				return this;
			}
			Builder* Writer(string writer) {
				this->writer = writer;
				return this;
			}
			Builder* Comment(string comment) {
				this->comment = comment;
				return this;
			}
			Builder* WritedAt(string writedAt) {
				this->writedAt = writedAt;
				return this;
			}
			PostingCommentProfile* Build() {
				return new PostingCommentProfile(*this);
			}

		private:
			string attachmentImageUrl;
			string writer;
			string comment;
			string writedAt;
		};

	public:
		PostingCommentProfile();
		PostingCommentProfile(string attachmentImageUrl, string writer, string comment, string writedAt);
		PostingCommentProfile(const PostingCommentProfile& source);
		PostingCommentProfile(Builder builder);
		virtual ~PostingCommentProfile();
		PostingCommentProfile& operator=(const PostingCommentProfile& source);

		virtual void Accept(DrawingGenerator* drawingGenerator);
		virtual Profile* Clone();

	private:
		string attachmentImageUrl;
		string writer;
		string comment;
		string writedAt;
	};
}

#endif // _POSTINGCOMMENTPROFILE_H