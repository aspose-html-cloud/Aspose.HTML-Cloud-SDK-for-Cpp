/**
* --------------------------------------------------------------------------------------------------------------------
* <copyright company="Aspose" file="PdfMetadata.h">
*  Copyright (c) 2022 Aspose.HTML for Cloud
* </copyright>
* <summary>
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
* </summary>
* --------------------------------------------------------------------------------------------------------------------
*/

#ifndef COM_ASPOSE_API_PdfMetadata_H_
#define COM_ASPOSE_API_PdfMetadata_H_

#include <boost/optional.hpp>
#include "ModelBase.h"

namespace com {
namespace aspose {
namespace model {

/// <summary>
/// PDF document information (/Info dictionary) metadata.
/// Only meaningful when the conversion output format is PDF.
/// All fields are optional; omitted fields keep the engine default.
/// </summary>
class PdfMetadata : public ModelBase
{
public:
    ASPOSE_DLL_EXPORT PdfMetadata();
    ASPOSE_DLL_EXPORT ~PdfMetadata();

    /// ModelBase overrides
    ASPOSE_DLL_EXPORT void validate() override;
    ASPOSE_DLL_EXPORT web::json::value toJson() const override;
    ASPOSE_DLL_EXPORT void fromJson(web::json::value& json) override;
    ASPOSE_DLL_EXPORT std::string toString() const override;

    ASPOSE_DLL_EXPORT void toMultipart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) const override;
    ASPOSE_DLL_EXPORT void fromMultiPart(std::shared_ptr<MultipartFormData> multipart, const utility::string_t& namePrefix) override;

    /// Setters — all return this* for chaining
    ASPOSE_DLL_EXPORT PdfMetadata* setTitle(const utility::string_t& value);
    ASPOSE_DLL_EXPORT PdfMetadata* setAuthor(const utility::string_t& value);
    ASPOSE_DLL_EXPORT PdfMetadata* setSubject(const utility::string_t& value);
    ASPOSE_DLL_EXPORT PdfMetadata* setKeywords(const utility::string_t& value);
    ASPOSE_DLL_EXPORT PdfMetadata* setCreator(const utility::string_t& value);
    ASPOSE_DLL_EXPORT PdfMetadata* setProducer(const utility::string_t& value);
    ASPOSE_DLL_EXPORT PdfMetadata* setCreationDate(const utility::string_t& value);
    ASPOSE_DLL_EXPORT PdfMetadata* setModificationDate(const utility::string_t& value);

private:
    boost::optional<utility::string_t> m_title;
    boost::optional<utility::string_t> m_author;
    boost::optional<utility::string_t> m_subject;
    boost::optional<utility::string_t> m_keywords;
    boost::optional<utility::string_t> m_creator;
    boost::optional<utility::string_t> m_producer;
    boost::optional<utility::string_t> m_creationDate;
    boost::optional<utility::string_t> m_modificationDate;
};

}
}
}

#endif /* COM_ASPOSE_API_PdfMetadata_H_ */
